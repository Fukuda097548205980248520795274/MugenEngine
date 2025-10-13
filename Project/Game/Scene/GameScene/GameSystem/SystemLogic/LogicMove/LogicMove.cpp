#include "LogicMove.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="t"></param>
void LogicMove::Initialize(float t)
{
	t_ = t;
}

/// <summary>
/// 方向ベクトルで移動ベクトルを求める
/// </summary>
/// <param name="direction"></param>
/// <returns></returns>
Vector3 LogicMove::GetMoveVelocity(const Vector3& direction)
{
	// 線形補間で移動ベクトルを求める
	return velocity_ = Lerp(velocity_, direction, t_);
}