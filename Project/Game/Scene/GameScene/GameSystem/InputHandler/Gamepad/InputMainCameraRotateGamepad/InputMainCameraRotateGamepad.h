#pragma once
#include "MugenEngine.h"

class InputMainCameraRotateGamepad
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(float rotateSpeed);

	/// <summary>
	/// スティックに合わせて方向ベクトルを求める
	/// </summary>
	/// <returns></returns>
	Vector3 GetMoveDirection();

	/// <summary>
	/// 回転速度を取得する
	/// </summary>
	/// <returns></returns>
	float GetRotateSpeed();



private:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// デッドゾーン
	float deadzone_ = 0.3f;

	// 回転速度
	float rotateSpeed_ = 0.0f;
};

