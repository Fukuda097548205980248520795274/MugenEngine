#include "AudioStore.h"

/// <summary>
/// デストラクタ
/// </summary>
AudioData::~AudioData()
{
	// ウェーブフォーマットの終了処理
	CoTaskMemFree(waveFormat);
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


	// MFの初期化
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
	MFShutdown();
	// XAudio2インスタンスを破棄する
	xAudio2_.Reset();
}

/// <summary>
/// オーディオファイルを読み込む
/// </summary>
/// <param name="filePath"></param>
uint32_t AudioStore::LoadAudio(const std::string& filePath)
{
	// 同じファイルパスを見つけたら、そのハンドルを返す
	for (std::unique_ptr<AudioData>& data : audioData_)
	{
		if (strcmp(filePath.c_str(), data->filePath.c_str()) == 0)
			return data->soundHandle;
	}


	// wStringに変換する
	const std::wstring filePathW = ConvertString(filePath);

	// ソースレーダを作成する
	IMFSourceReader* pMFSourceReader{ nullptr };
	HRESULT hr = MFCreateSourceReaderFromURL(filePathW.c_str(), NULL, &pMFSourceReader);
	assert(SUCCEEDED(hr));

	// メディアタイプの作成
	IMFMediaType* pMFMediaType{ nullptr };
	hr = MFCreateMediaType(&pMFMediaType);
	assert(SUCCEEDED(hr));

	// ソースレーダとメディアタイプの設定
	pMFMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	pMFMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	pMFSourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, pMFMediaType);

	// メディアタイプを解放し、再度作成する
	pMFMediaType->Release();
	pMFMediaType = nullptr;
	pMFSourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &pMFMediaType);


	// オーディオデータを作成する
	std::unique_ptr<AudioData> audioDatum = std::make_unique<AudioData>();
	audioDatum->filePath = filePath;

	// サウンドハンドルを取得する
	uint32_t soundHandle = static_cast<uint32_t>(audioData_.size());
	audioDatum->soundHandle = soundHandle;

	// ウェーブフォーマットを作成する
	MFCreateWaveFormatExFromMFMediaType(pMFMediaType, &audioDatum->waveFormat, nullptr);

	while (true)
	{
		IMFSample* pMFSample{ nullptr };
		DWORD dwStreamFlags{ 0 };
		pMFSourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &dwStreamFlags, nullptr, &pMFSample);

		if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			break;
		}

		IMFMediaBuffer* pMFMediaBuffer{ nullptr };
		pMFSample->ConvertToContiguousBuffer(&pMFMediaBuffer);

		BYTE* pBuffer{ nullptr };
		DWORD cbCurrentLength{ 0 };
		pMFMediaBuffer->Lock(&pBuffer, nullptr, &cbCurrentLength);

		audioDatum->mediaData.resize(audioDatum->mediaData.size() + cbCurrentLength);
		memcpy(audioDatum->mediaData.data() + audioDatum->mediaData.size() - cbCurrentLength, pBuffer, cbCurrentLength);

		pMFMediaBuffer->Unlock();

		// 解放
		pMFMediaBuffer->Release();
		pMFSample->Release();
	}

	// 解放
	pMFMediaType->Release();
	pMFSourceReader->Release();

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
uint32_t AudioStore::PlayAudio(uint32_t soundHandle, float volume)
{
	// プレイデータを生成する
	std::unique_ptr<PlayData> playDatum = std::make_unique<PlayData>();

	// プレイハンドルを作成する
	uint32_t playHandle = 0;
	while (playHandle == 0)
	{
		playHandle = rand() % 1000000 + 1;

		for (std::unique_ptr<PlayData>& data : playData_)
		{
			if (playHandle == data->playHandle)
			{
				playHandle = 0;
				break;
			}
		}
	}
	playDatum->playHandle = playHandle;


	// ソースボイスを生成する
	HRESULT hr = xAudio2_->CreateSourceVoice(&playDatum->pSourceVoice, audioData_[soundHandle]->waveFormat);
	assert(SUCCEEDED(hr));

	XAUDIO2_BUFFER buffer{ 0 };
	buffer.pAudioData = audioData_[soundHandle]->mediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(audioData_[soundHandle]->mediaData.size());
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
void AudioStore::StopAudio(uint32_t playHandle)
{
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (playHandle == playDatum->playHandle)
		{
			playDatum->pSourceVoice->Stop(0);
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
bool AudioStore::IsAudioPlay(uint32_t playHandle)
{
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (playHandle == playDatum->playHandle)
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
void AudioStore::SetVolume(uint32_t playHandle, float volume)
{
	const float kMaxSoundVolume = 1.0f;
	const float kMinSoundVolume = 0.0f;

	// 規格外の音にならぬようにする
	volume = std::max(kMinSoundVolume, volume);
	volume = std::min(kMaxSoundVolume, volume);

	// ハンドルが一致する構造体を探す
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (playHandle == playDatum->playHandle)
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
void AudioStore::SetPitch(uint32_t playHandle, float pitch)
{
	// ハンドルが一致する構造体を探す
	for (std::unique_ptr<PlayData>& playDatum : playData_)
	{
		if (playHandle == playDatum->playHandle)
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
			// 音楽が終了したとき
			if (playDatum->pSourceVoice)
			{
				XAUDIO2_VOICE_STATE state;
				playDatum->pSourceVoice->GetState(&state);

				if (state.BuffersQueued <= 0)
				{
					return true;
				}
			} 
			else
			{
				// 音楽を停止させたとき
				return true;
			}

			return false;
		}
	);
}