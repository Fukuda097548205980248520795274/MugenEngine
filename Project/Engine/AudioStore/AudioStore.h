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

#include "../LogFile/LogFile.h"
#include "../Func/ConvertString/ConvertString.h"
#include "RandomUtil/RandomUtil.h"


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
	uint32_t soundHandle;
};

// プレイデータ
class PlayData
{
public:

	// プレイハンドル
	uint32_t playHandle;

	// ソースボイス
	IXAudio2SourceVoice* pSourceVoice;
};


// オーディオ格納場所
class AudioStore
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AudioStore();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	void Initialize(LogFile* logFile);

	/// <summary>
	/// オーディオファイルを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	uint32_t LoadAudio(const std::string& filePath);

	/// <summary>
	/// オーディオを流す
	/// </summary>
	/// <param name="soundHandle"></param>
	/// <param name="valume"></param>
	/// <returns></returns>
	uint32_t PlayAudio(uint32_t soundHandle, float volume);

	/// <summary>
	/// 音声を停止する
	/// </summary>
	/// <param name="playHandle"></param>
	void StopAudio(uint32_t playHandle);

	/// <summary>
	/// 音楽が再生されているかどうか
	/// </summary>
	/// <param name="playHandle"></param>
	bool IsAudioPlay(uint32_t playHandle);

	/// <summary>
	/// 音量を設定する
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="setVolume"></param>
	void SetVolume(uint32_t playHandle, float volume);

	/// <summary>
	/// ピッチを設定する
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="pitch"></param>
	void SetPitch(uint32_t playHandle, float pitch);

	/// <summary>
	/// 流れているオーディオを削除する
	/// </summary>
	void DeletePlayAudio();


private:

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	// ログファイル
	LogFile* logFile_ = nullptr;

	// 乱数生成
	RandomUtil* randomUtil_ = nullptr;



	// XAudio2
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2_ = nullptr;

	// マスターボイス
	IXAudio2MasteringVoice* masterVoice_ = nullptr;

	// オーディオデータ配列
	std::vector<std::unique_ptr<AudioData>> audioData_;

	// プレイデータ配列
	std::list<std::unique_ptr<PlayData>> playData_;
};

