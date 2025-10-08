#include "LogicMoveSpeed.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="speed"></param>
void LogicMoveSpeed::Initialize(float speed)
{
	speed_ = speed;
}

/// <summary>
/// 移動ベクトルを速度ベクトルにする
/// </summary>
/// <returns></returns>
Vector3 LogicMoveSpeed::GetSpeedVector(const Vector3& moveVector)
{
	// 速度ベクトル
	Vector3 speedVector = Vector3(0.0f, 0.0f, 0.0f);

	// 移動速度を乗算する
	speedVector = speed_ * moveVector;

	return speedVector;
}