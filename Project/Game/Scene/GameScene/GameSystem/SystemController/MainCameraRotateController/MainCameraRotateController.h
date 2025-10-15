#pragma once
#include "../../InputHandler/Gamepad/InputMainCameraRotateGamepad/InputMainCameraRotateGamepad.h"
#include "../../InputHandler/Keyboard/InputMainCameraRotateKey/InputMainCameraRotateKey.h"
#include "../../SystemLogic/LogicMainCameraRotateSpeed/LogicMainCameraRotateSpeed.h"

class MainCameraRotateController
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 回転の値を取得する
	/// </summary>
	/// <returns></returns>
	Vector3 GetRotateValue();


private:


	// エンジン
	const MugenEngine* engine_ = nullptr;

	/// <summary>
	/// キーボード操作での回転の値を取得する
	/// </summary>
	Vector3 GetRotateValueKeyboard();

	/// <summary>
	/// ゲームパッド操作での回転の値を取得する
	/// </summary>
	Vector3 GetRotateValueGamepad();


	// メインカメラ回転入力　キーボード
	std::unique_ptr<InputMainCameraRotateKey> inputMainCameraRotatekeyboard_ = nullptr;

	// メインカメラ回転入力　ゲームパッド
	std::unique_ptr<InputMainCameraRotateGamepad> inputMainCameraRotateGamepad_ = nullptr;

	// メインカメラ回転速度ロジック
	std::unique_ptr<LogicMainCameraRotateSpeed> logicMainCameraRotateSpeed_ = nullptr;

	// カメラの回転速度
	float rotateSpeed_ = 1.8f;
};

