#include "LogicMainCameraRotateSpeed.h"

/// <summary>
/// 最大速度を入れて、補完した速度を求める
/// </summary>
/// <param name="maxRotateSpeed"></param>
float LogicMainCameraRotateSpeed::GetRotateSpeed(float maxRotateSpeed)
{
	rotateSpeed_ = Lerp(rotateSpeed_, maxRotateSpeed , 0.1f);
	return rotateSpeed_;
}