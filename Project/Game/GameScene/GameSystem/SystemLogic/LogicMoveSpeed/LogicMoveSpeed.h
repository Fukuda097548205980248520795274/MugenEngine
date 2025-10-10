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

	/// <summary>
	/// 最大速度のSetter
	/// </summary>
	/// <param name="maxSpeed"></param>
	void SetMaxSpeed(float maxSpeed) { maxSpeed_ = maxSpeed; };


private:

	// 移動速度
	float speed_ = 0.0f;

	// 最大速度
	float maxSpeed_ = 0.0f;
};

