#pragma once
#define NOMINMAX
#include <algorithm>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <xaudio2.h>
#include <wrl.h>
#include <cassert>
#include <list>
#include <mferror.h>

#include "../LogFile/LogFile.h"
#include "Func/ConvertString/ConvertString.h"
#include "Func/Random/Random.h"
#include "Handle/Handle.h"


// オーディオデータ
class AudioData
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AudioData();

	// ファイルパス
	std::string filePath;

	// フォーマット
	WAVEFORMATEX* waveFormat;

	// メディアデータ
	std::vector<BYTE> mediaData;

	// サウンドハンドル
	SoundHandle handle;
};

// プレイデータ
class PlayData
{
public:

	// プレイハンドル
	PlayHandle handle;

	// ソースボイス
	IXAudio2SourceVoice* pSourceVoice;
};


// オーディオ格納場所
class AudioStore
{
public:
	
	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static AudioStore* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	void Initialize(LogFile* logFile);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// オーディオファイルを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	SoundHandle LoadAudio(const std::string& filePath);

	/// <summary>
	/// オーディオを流す
	/// </summary>
	/// <param name="soundHandle"></param>
	/// <param name="valume"></param>
	/// <returns></returns>
	PlayHandle PlayAudio(SoundHandle handle, float volume);

	/// <summary>
	/// 音声を停止する
	/// </summary>
	/// <param name="playHandle"></param>
	void StopAudio(PlayHandle handle);

	/// <summary>
	/// 音楽が再生されているかどうか
	/// </summary>
	/// <param name="playHandle"></param>
	bool IsAudioPlay(PlayHandle handle);

	/// <summary>
	/// 音量を設定する
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="setVolume"></param>
	void SetVolume(PlayHandle handle, float volume);

	/// <summary>
	/// ピッチを設定する
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="pitch"></param>
	void SetPitch(PlayHandle handle, float pitch);

	/// <summary>
	/// 流れているオーディオを削除する
	/// </summary>
	void DeletePlayAudio();

	// Microsoft::WRL:: 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


private:

	// シングルトン
	AudioStore() = default;
	~AudioStore() = default;
	AudioStore(AudioStore&) = delete;
	AudioStore& operator=(AudioStore&) = delete;

	// インスタンス
	static AudioStore* instance_;



	// ログファイル
	LogFile* logFile_ = nullptr;



	// XAudio2
	ComPtr<IXAudio2> xAudio2_ = nullptr;

	// マスターボイス
	IXAudio2MasteringVoice* masterVoice_ = nullptr;

	// オーディオデータ配列
	std::vector<std::unique_ptr<AudioData>> audioData_;

	// プレイデータ配列
	std::list<std::unique_ptr<PlayData>> playData_;
};

