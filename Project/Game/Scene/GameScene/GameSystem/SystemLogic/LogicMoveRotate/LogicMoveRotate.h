#pragma once
#include "MugenEngine.h"

class LogicMoveRotate
{
public:

	/// <summary>
	/// 最終的な向きを更新する
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	void UpdateGoalDirection(const Vector3& move);

	/// <summary>
	/// 最短角度補間で回転を取得する
	/// </summary>
	/// <param name="currentDirection"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	float GetMoveRotate(float currentRotate, float t);


private:

	// 向き
	Vector3 direction_ = Vector3(0.0f, 0.0f, 0.0f);
};

