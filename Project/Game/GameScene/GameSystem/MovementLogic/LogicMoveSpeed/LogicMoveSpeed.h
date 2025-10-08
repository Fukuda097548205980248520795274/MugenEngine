#pragma once
#include "MugenEngine.h"

class LogicMoveSpeed
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="speed"></param>
	void Initialize(float speed);

	/// <summary>
	/// 移動ベクトルを速度ベクトルにする
	/// </summary>
	/// <returns></returns>
	Vector3 GetSpeedVector(const Vector3& moveVector);


private:

	// 移動速度
	float speed_ = 0.0f;
};

