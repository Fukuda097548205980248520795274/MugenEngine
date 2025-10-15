#include "MainCameraRotateController.h"

/// <summary>
/// 初期化
/// </summary>
void MainCameraRotateController::Initialize()
{
	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// メインカメラ回転入力ゲームパッドの生成と初期化
	inputMainCameraRotateGamepad_ = std::make_unique<InputMainCameraRotateGamepad>();
	inputMainCameraRotateGamepad_->Initialize(rotateSpeed_);

	// メインカメラ回転入力キーボードの生成と初期化
	inputMainCameraRotatekeyboard_ = std::make_unique<InputMainCameraRotateKey>();
	inputMainCameraRotatekeyboard_->Initialize(DIK_UP, DIK_LEFT, DIK_DOWN, DIK_RIGHT, rotateSpeed_);

	// メインカメラ回転速度ロジックの生成
	logicMainCameraRotateSpeed_ = std::make_unique<LogicMainCameraRotateSpeed>();
}

/// <summary>
/// 回転の値を取得する
/// </summary>
/// <returns></returns>
Vector3 MainCameraRotateController::GetRotateValue()
{
	// ゲームパッド
	if (engine_->IsGamepadEnable(0))
	{
		return GetRotateValueGamepad();
	}
	else
	{
		// キーボード
		return GetRotateValueKeyboard();
	}
}



/// <summary>
/// キーボード操作での回転の値を取得する
/// </summary>
Vector3 MainCameraRotateController::GetRotateValueKeyboard()
{
	// 回転
	Vector3 rotate = Vector3(0.0f, 0.0f, 0.0f);

	// 回転方向を取得する
	Vector3 rotateDirection = inputMainCameraRotatekeyboard_->GetRotateDirection();

	// 最大回転速度を取得する
	float maxRotateSpeed = inputMainCameraRotatekeyboard_->GetRotateSpeed();

	// 回転と速度を乗算する
	rotate = rotateDirection * logicMainCameraRotateSpeed_->GetRotateSpeed(maxRotateSpeed);

	return rotate * engine_->GetDeltaTime();
}

/// <summary>
/// ゲームパッド操作での回転の値を取得する
/// </summary>
Vector3 MainCameraRotateController::GetRotateValueGamepad()
{
	// 回転
	Vector3 rotate = Vector3(0.0f, 0.0f, 0.0f);

	// 回転方向を取得する
	Vector3 rotateDirection = inputMainCameraRotateGamepad_->GetRotateDirection();

	// 最大回転速度を取得する
	float maxRotateSpeed = inputMainCameraRotateGamepad_->GetRotateSpeed();

	// 回転と速度を乗算する
	rotate = rotateDirection * logicMainCameraRotateSpeed_->GetRotateSpeed(maxRotateSpeed);

	return rotate * engine_->GetDeltaTime();
}