#include "InputMainCameraRotateGamepad.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void InputMainCameraRotateGamepad::Initialize(float rotateSpeed)
{
	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// 引数を受け取る
	rotateSpeed_ = rotateSpeed;
}

/// <summary>
/// スティックに合わせて方向ベクトルを求める
/// </summary>
/// <returns></returns>
Vector3 InputMainCameraRotateGamepad::GetMoveDirection()
{
	// 方向ベクトル
	Vector3 direction = Vector3(0.0f, 0.0f, 0.0f);

	// ゲームパッドが使えるかどうか
	if (engine_->IsGamepadEnable(0) == false)
		return direction;

	// スティックのベクトル
	Vector2 stick = engine_->GetGamepadRightStick(0);

	// 距離
	float length = Length(stick);

	// デッドゾーンを越えたかどうか
	if (length < deadzone_)
		return direction;

	// 方向ベクトルに値を渡す
	direction = Vector3(-stick.y, stick.x, 0.0f);
	return direction;
}

/// <summary>
/// 回転速度を取得する
/// </summary>
/// <returns></returns>
float InputMainCameraRotateGamepad::GetRotateSpeed()
{
	// ゲームパッドが使えるかどうか
	if (engine_->IsGamepadEnable(0) == false)
		return 0.0f;

	// スティックのベクトル
	Vector2 stick = engine_->GetGamepadRightStick(0);

	// 距離
	float length = Length(stick);

	// デッドゾーンを越えたかどうか
	if (length < deadzone_)
		return 0.0f;

	return rotateSpeed_ * length;
}