#include "InputMoveGamepad.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void InputMoveGamepad::Initialize()
{
	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
}

/// <summary>
/// スティックに合わせて方向ベクトルを求める
/// </summary>
/// <returns></returns>
Vector3 InputMoveGamepad::GetMoveDirection()
{
	// 方向ベクトル
	Vector3 direction = Vector3(0.0f, 0.0f, 0.0f);

	// ゲームパッドが使えるかどうか
	if (engine_->IsGamepadEnable(0) == false)
		return direction;

	// スティックのベクトル
	Vector2 stick = engine_->GetGamepadLeftStick(0);

	// 距離
	float length = Length(stick);

	// デッドゾーンを越えたかどうか
	if (length < deadzone_)
		return direction;

	// 方向ベクトルに値を渡す
	direction = Vector3(stick.x, 0.0f, stick.y);
	return direction;
}