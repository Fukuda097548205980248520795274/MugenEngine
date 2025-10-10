#include "AudioStore.h"

/// <summary>
/// デストラクタ
/// </summary>
AudioData::~AudioData()
{
	if (waveFormat) {
		CoTaskMemFree(waveFormat);
		waveFormat = nullptr;
	}
	mediaData.clear();
}







/// <summary>
/// デストラクタ
/// </summary>
AudioStore::~AudioStore()
{
	// 終了処理
	Finalize();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
void AudioStore::Initialize(LogFile* logFile)
{
	// nullptrチェック
	assert(logFile);

	// 引数を受け取る
	logFile_ = logFile;


	// MFの初期化（ローカル版）
	MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);

	// XAudio2を初期化する
	HRESULT hr = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));
	logFile_->Log("SUCCEEDED : XAudio2 \n");

	// マスターボイスを生成する
	hr = xAudio2_->CreateMasteringVoice(&masterVoice_);
	assert(SUCCEEDED(hr));
	logFile_->Log("SUCCEEDED : MasterVoice \n");
}

/// <summary>
/// 終了処理
/// </summary>
void AudioStore::Finalize()
{

	// 全ての再生中の音声を停止・破棄する
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (playDatum->pSourceVoice)
		{
			playDatum->pSourceVoice->Stop(0);
			playDatum->pSourceVoice->DestroyVoice();
		}
	}
	// playData_ リストが unique_ptr であれば、ここで自動的に要素が解放される

	// MFの終了処理
	HRESULT hr = MFShutdown();
	assert(SUCCEEDED(hr));

	// XAudio2インスタンスを破棄する
	xAudio2_.Reset();
}

/// <summary>
/// オーディオファイルを読み込む
/// </summary>
/// <param name="filePath"></param>
SoundHandle AudioStore::LoadAudio(const std::string& filePath)
{
	// 同じファイルパスを見つけたら、そのハンドルを返す
	for (std::unique_ptr<AudioData>& data : audioData_)
	{
		if (strcmp(filePath.c_str(), data->filePath.c_str()) == 0)
			return data->handle;
	}

	// wStringに変換する
	const std::wstring filePathW = ConvertString(filePath);

	// ソースレーダを作成する
	ComPtr<IMFSourceReader> pMFSourceReader{ nullptr };
	HRESULT hr = MFCreateSourceReaderFromURL(filePathW.c_str(), NULL, &pMFSourceReader);
	assert(SUCCEEDED(hr));


	// メディアタイプの作成
	ComPtr<IMFMediaType> pReader{ nullptr };
	hr = MFCreateMediaType(&pReader);
	assert(SUCCEEDED(hr));

	// ソースレーダとメディアタイプの設定
	pReader->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	pReader->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	hr = pMFSourceReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, pReader.Get());
	assert(SUCCEEDED(hr));

	// メディアタイプを解放し、再度作成する
	ComPtr<IMFMediaType> pOutType;
	hr = pMFSourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &pOutType);
	assert(SUCCEEDED(hr));


	// オーディオデータを作成する
	std::unique_ptr<AudioData> audioDatum = std::make_unique<AudioData>();
	audioDatum->filePath = filePath;

	// サウンドハンドルを取得する
	SoundHandle soundHandle;
	soundHandle.value = static_cast<uint32_t>(audioData_.size());
	audioDatum->handle = soundHandle;

	// ウェーブフォーマットを作成する
	MFCreateWaveFormatExFromMFMediaType(pOutType.Get(), &audioDatum->waveFormat, nullptr);

	while (true)
	{
		ComPtr<IMFSample> pMFSample{ nullptr };

		DWORD streamIndex = 0;
		DWORD flags = 0;
		LONGLONG llTimeStamp = 0;

		hr = pMFSourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, &streamIndex, &flags, &llTimeStamp, &pMFSample);
		assert(SUCCEEDED(hr));

		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)break;

		if (pMFSample)
		{
			ComPtr<IMFMediaBuffer> pBuffer{ nullptr };
			hr = pMFSample->ConvertToContiguousBuffer(&pBuffer);
			assert(SUCCEEDED(hr));

			BYTE* pData{ nullptr };
			DWORD currentLength = 0;
			hr = pBuffer->Lock(&pData, nullptr, &currentLength);
			assert(SUCCEEDED(hr));

			audioDatum->mediaData.resize(audioDatum->mediaData.size() + currentLength);
			memcpy(audioDatum->mediaData.data() + audioDatum->mediaData.size() - currentLength, pData, currentLength);

			pBuffer->Unlock();
		}
	}

	// 配列に登録する
	audioData_.push_back(std::move(audioDatum));

	return soundHandle;
}


/// <summary>
/// オーディオを流す
/// </summary>
/// <param name="soundHandle"></param>
/// <param name="valume"></param>
/// <returns></returns>
PlayHandle AudioStore::PlayAudio(SoundHandle handle, float volume)
{
	// プレイデータを生成する
	std::unique_ptr<PlayData> playDatum = std::make_unique<PlayData>();

	// プレイハンドルを作成する
	PlayHandle playHandle{};
	while (playHandle.value == 0)
	{
		playHandle.value = GetRandomRange(1, 10000000);

		for (std::unique_ptr<PlayData>& data : playData_)
		{
			if (playHandle.value == data->handle.value)
			{
				playHandle.value = 0;
				break;
			}
		}
	}
	playDatum->handle = playHandle;


	// ソースボイスを生成する
	HRESULT hr = xAudio2_->CreateSourceVoice(&playDatum->pSourceVoice, audioData_[handle.value]->waveFormat);
	assert(SUCCEEDED(hr));

	XAUDIO2_BUFFER buffer{ 0 };
	buffer.pAudioData = audioData_[handle.value]->mediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(audioData_[handle.value]->mediaData.size());
	playDatum->pSourceVoice->SubmitSourceBuffer(&buffer);

	const float kMaxSoundVolume = 1.0f;
	const float kMinSoundVolume = 0.0f;

	// 規格外の音にならぬようにする
	volume = std::max(kMinSoundVolume, volume);
	volume = std::min(kMaxSoundVolume, volume);

	playDatum->pSourceVoice->SetVolume(volume);

	playDatum->pSourceVoice->Start(0);

	// リストに登録する
	playData_.push_back(std::move(playDatum));

	return playHandle;
}


/// <summary>
/// 音声を停止する
/// </summary>
/// <param name="playHandle"></param>
void AudioStore::StopAudio(PlayHandle handle)
{
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (handle.value == playDatum->handle.value)
		{
			playDatum->pSourceVoice->Stop(0);
			playDatum->pSourceVoice->DestroyVoice();
			playDatum->pSourceVoice = nullptr;

			return;
		}
	}

	return;
}

/// <summary>
/// 音楽が再生されているかどうか
/// </summary>
/// <param name="playHandle"></param>
bool AudioStore::IsAudioPlay(PlayHandle handle)
{
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (handle.value == playDatum->handle.value)
		{
			return true;
		}
	}

	return false;
}


/// <summary>
/// 音量を設定する
/// </summary>
/// <param name="playHandle"></param>
/// <param name="setVolume"></param>
void AudioStore::SetVolume(PlayHandle handle, float volume)
{
	const float kMaxSoundVolume = 1.0f;
	const float kMinSoundVolume = 0.0f;

	// 規格外の音にならぬようにする
	volume = std::max(kMinSoundVolume, volume);
	volume = std::min(kMaxSoundVolume, volume);

	// ハンドルが一致する構造体を探す
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (handle.value == playDatum->handle.value)
		{
			playDatum->pSourceVoice->SetVolume(volume);

			return;
		}
	}

	return;
}

/// <summary>
/// ピッチを設定する
/// </summary>
/// <param name="playHandle"></param>
/// <param name="pitch"></param>
void AudioStore::SetPitch(PlayHandle handle, float pitch)
{
	// ハンドルが一致する構造体を探す
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (handle.value == playDatum->handle.value)
		{
			playDatum->pSourceVoice->SetFrequencyRatio(pitch);

			return;
		}
	}

	return;
}


/// <summary>
/// 流れているオーディオを削除する
/// </summary>
void AudioStore::DeletePlayAudio()
{
	playData_.remove_if([](std::unique_ptr<PlayData>& playDatum)
		{
			if (playDatum->pSourceVoice)
			{
				XAUDIO2_VOICE_STATE state;
				playDatum->pSourceVoice->GetState(&state);

				if (state.BuffersQueued <= 0)
				{
					playDatum->pSourceVoice->DestroyVoice();
					playDatum->pSourceVoice = nullptr;
					return true;
				}
			} else
			{
				return true;
			}
			return false;
		}
	);
}