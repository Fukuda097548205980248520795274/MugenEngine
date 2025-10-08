#pragma once
#include "MugenEngine.h"

class LogicMove
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="t"></param>
	void Initialize(float t);

	/// <summary>
	/// 方向ベクトルで移動ベクトルを求める
	/// </summary>
	/// <param name="direction"></param>
	/// <returns></returns>
	Vector3 GetMoveVelocity(const Vector3& direction);


private:

	// 現在の移動ベクトル
	Vector3 velocity_ = Vector3(0.0f, 0.0f, 0.0f);

	// 補間
	float t_ = 1.0f;
};

