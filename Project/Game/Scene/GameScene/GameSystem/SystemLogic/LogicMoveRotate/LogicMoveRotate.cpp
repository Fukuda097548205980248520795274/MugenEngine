#include "LogicMoveRotate.h"

/// <summary>
/// 最終的な向きを更新する
/// </summary>
/// <param name="move"></param>
/// <returns></returns>
void LogicMoveRotate::UpdateGoalDirection(const Vector3& move)
{
	// 移動していない
	if (move.x == 0.0f && move.y == 0.0f && move.z == 0)
		return;

	// 正規化し、向きを取得する
	direction_ = Normalize(move);
}

/// <summary>
/// 最短角度補間で回転を取得する
/// </summary>
/// <param name="currentDirection"></param>
/// <param name="t"></param>
/// <returns></returns>
float LogicMoveRotate::GetMoveRotate(float currentRotate, float t)
{
	// 現在の角度
	float currentRadian = currentRotate;

	// 最終的な角度
	float goalRadian = std::atan2f(direction_.x, direction_.z);

	// 角度の差
	float diff = goalRadian - currentRadian;

	// 360度内にとどめる
	diff = std::fmod(diff, std::numbers::pi_v<float> * 2.0f);

	if (diff > std::numbers::pi_v<float>)
	{
		diff += -2.0f * std::numbers::pi_v<float>;
	}
	else if (diff < -std::numbers::pi_v<float>)
	{
		diff += 2.0f * std::numbers::pi_v<float>;
	}

	// 線形補間
	currentRadian = currentRadian + diff * t;

	return currentRadian;
}