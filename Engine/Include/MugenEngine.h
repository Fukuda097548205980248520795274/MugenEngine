#pragma once
#include <memory>
#include <dxgidebug.h>

#include "WinApp/WinApp.h"
#include "LogFile/LogFile.h"
#include "DirectXBase/DirectXBase.h"
#include "Func/CrushHandler/CrushHandler.h"
#include "Input/Input.h"
#include "AudioStore/AudioStore.h"

// マウスボタン
enum MouseButton
{
	// 左ボタン
	kMouseButtonLeft,

	// 右ボタン
	kMouseButtonRight,

	// 中央ボタン
	kMouseButtonCenter
};

// 無限エンジン
class MugenEngine
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MugenEngine();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title);

	/// <summary>
	/// ウィンドウにメッセージを渡して応答する
	/// </summary>
	/// <returns></returns>
	bool ProcessMessage() { return winApp_->ProcessMessage(); }

	/// <summary>
	/// フレーム開始処理
	/// </summary>
	void FrameStart();

	/// <summary>
	/// フレーム終了処理
	/// </summary>
	void FrameEnd();



	/// <summary>
	/// キー入力（Press）
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns></returns>
	bool GetKeyPress(BYTE key) const { return input_->GetKeyPress(key); }

	/// <summary>
	/// キー入力（Trigger）
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns></returns>
	bool GetKeyTrigger(BYTE key) const { return input_->GetKeyTrigger(key); }

	/// <summary>
	/// キー入力（Release）
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns></returns>
	bool GetKeyRelease(BYTE key) const { return input_->GetKeyRelease(key); }

	/// <summary>
	/// マウスボタン（Press）
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetMouseButtonPress(MouseButton mouseButton) const { return input_->GetMousePress(static_cast<uint32_t>(mouseButton)); };

	/// <summary>
	/// マウスボタン（Trigger）
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetMouseButtonTrigger(MouseButton mouseButton) const { return input_->GetMouseTrigger(static_cast<uint32_t>(mouseButton)); };

	/// <summary>
	/// マウスボタン（Release）
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetMouseButtonRelease(MouseButton mouseButton) const { return input_->GetMouseRelease(static_cast<uint32_t>(mouseButton)); };

	/// <summary>
	/// マウスの移動量のGetter
	/// </summary>
	/// <returns></returns>
	Vector2 GetMouseVelocity() const { return input_->GetMouseVelocity(); }

	/// <summary>
	/// マウスホイールが上回転しているかどうか
	/// </summary>
	/// <returns></returns>
	bool GetMouseWheelUp() const { return input_->GetMouseWheelUp(); }

	/// <summary>
	/// マウスホイールが下回転しているかどうか
	/// </summary>
	/// <returns></returns>
	bool GetMouseWheelDown()  const { return input_->GetMouseWheelDown(); }

	/// <summary>
	/// マウスホイールの回転量のGetter
	/// </summary>
	/// <returns></returns>
	float GetMouseWheelVelocity() const { return input_->GetMouseWheelVelocity(); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gamepadNumber"></param>
	/// <returns></returns>
	bool IsGamepadEnable(DWORD gamepadNumber) const { return input_->IsGamepadEnable(gamepadNumber); }

	/// <summary>
	/// ゲームパッドのボタンの入力情報（Press）
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <param name="wButtons">指定のボタン</param>
	/// <returns></returns>
	bool GetGamepadButtonPress(DWORD gamepadNumber, DWORD wButtons) const { return input_->GetGamepadButtonPress(gamepadNumber, wButtons); }

	/// <summary>
	/// ゲームパッドのボタンの入力情報（Press）
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <param name="wButtons">指定のボタン</param>
	/// <returns></returns>
	bool GetGamepadButtonTrigger(DWORD gamepadNumber, DWORD wButtons) const { return input_->GetGamepadButtonTrigger(gamepadNumber, wButtons); }

	/// <summary>
	/// ゲームパッドのボタンの入力情報（Press）
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <param name="wButtons">指定のボタン</param>
	/// <returns></returns>
	bool GetGamepadButtonRelease(DWORD gamepadNumber, DWORD wButtons) const { return input_->GetGamepadButtonRelease(gamepadNumber, wButtons); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gamepadNumber"></param>
	/// <returns></returns>
	Vector2 GetGamepadLeftStick(DWORD gamepadNumber) const { return input_->GetGamepadLeftStick(gamepadNumber); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gamepadNumber"></param>
	/// <returns></returns>
	Vector2 GetGamepadRightStick(DWORD gamepadNumber) const { return input_->GetGamepadRightStick(gamepadNumber); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gamepadNumber"></param>
	/// <returns></returns>
	float GetGamepadLeftTrigger(DWORD gamepadNumber) const { return input_->GetGamepadLeftTrigger(gamepadNumber); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="gamepadNumber"></param>
	/// <returns></returns>
	float GetGamepadRightTrigger(DWORD gamepadNumber) const { return input_->GetGamepadRightTrigger(gamepadNumber); }




	/// <summary>
	/// スクリーン横幅のGetter
	/// </summary>
	/// <returns></returns>
	int32_t GetScreenWidth()const { return winApp_->GetClientWidth(); }

	/// <summary>
	/// スクリーン縦幅のGetter
	/// </summary>
	/// <returns></returns>
	int32_t GetScreenHeight()const { return winApp_->GetClientHeight(); }


	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath)const { return directXBase_->LoadTexture(filePath); }


	/// <summary>
	/// 音声データを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadAudio(const std::string& filePath) const { return audioStore_->LoadAudio(filePath); }

	/// <summary>
	/// 音量の設定
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="volume"></param>
	void SetVolume(uint32_t playHandle, float volume) const { audioStore_->SetVolume(playHandle, volume); }

	/// <summary>
	/// ピッチの設定
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="pitch"></param>
	void SetPitch(uint32_t playHandle, float pitch)const { audioStore_->SetPitch(playHandle, pitch); }

	/// <summary>
	/// 音声データを再生する
	/// </summary>
	/// <param name="soundHandle"></param>
	uint32_t PlayAudio(uint32_t soundHandle, float volume) const { return audioStore_->PlayAudio(soundHandle, volume); }

	/// <summary>
	/// 音声データを停止する
	/// </summary>
	/// <param name="playHandle"></param>
	void StopAudio(uint32_t playHandle) const { audioStore_->StopAudio(playHandle); }

	/// <summary>
	/// 音楽が再生されているかどうか
	/// </summary>
	/// <param name="playHandle"></param>
	/// <returns></returns>
	bool IsAudioPlay(uint32_t playHandle)const { return audioStore_->IsAudioPlay(playHandle); }


	// スプライトを描画する
	void DrawSprite(const WorldTransform2D* worldTransform, const Camera2D* camera, uint32_t textureHandle)const
	{ directXBase_->DrawSprite(worldTransform,camera, textureHandle); }

	/// <summary>
	/// UV球を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="segment"></param>
	/// <param name="ring"></param>
	void DrawUVSphere(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle,
		int32_t segment, int32_t ring) const
	{directXBase_->DrawUVSphere(worldTransform,uvTransform, camera, textureHandle, segment, ring);}

	/// <summary>
	/// 立方体を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	void DrawCube(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, uint32_t textureHandle) const
	{directXBase_->DrawCube(worldTransform,uvTransform, camera, textureHandle);}


private:

	// クライアント領域横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域縦幅
	const int32_t* kClientHeight_ = nullptr;


	// ログファイル
	LogFile* logFile_ = nullptr;

	// ウィンドウズアプリケーション
	WinApp* winApp_ = nullptr;
	
	// DirectXのベース
	DirectXBase* directXBase_ = nullptr;

	// 入力
	Input* input_ = nullptr;

	// オーディオ格納場所
	AudioStore* audioStore_ = nullptr;
};

