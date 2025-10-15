#include "InputMainCameraRotateKey.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="upKey"></param>
/// <param name="leftKey"></param>
/// <param name="downKey"></param>
/// <param name="rightKey"></param>
/// <param name="rotateSpeed"></param>
void InputMainCameraRotateKey::Initialize(BYTE upKey, BYTE leftKey, BYTE downKey, BYTE rightKey, float rotateSpeed)
{
	// 引数を受け取る
	upKey_ = upKey;
	leftKey_ = leftKey;
	downKey_ = downKey;
	rightKey_ = rightKey;
	rotateSpeed_ = rotateSpeed;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
}

/// <summary>
/// 回転の方向を取得する
/// </summary>
/// <returns></returns>
Vector3 InputMainCameraRotateKey::GetRotateDirection()
{
	// 回転の方向
	Vector3 rotateDirecton = Vector3(0.0f, 0.0f, 0.0f);

	// 上キー
	if (IsUp())
	{
		rotateDirecton.x = 1.0f;
	}

	// 左キー
	if (IsLeft())
	{
		rotateDirecton.y = -1.0f;
	}

	// 下キー
	if (IsDown())
	{
		rotateDirecton.x = -1.0f;
	}

	// 右キー
	if (IsRight())
	{
		rotateDirecton.y = 1.0f;
	}

	return rotateDirecton;
}