#pragma once
#include "MugenEngine.h"

class LogicMainCameraRotateSpeed
{
public:

	/// <summary>
	/// 最大速度を入れて、補完した速度を求める
	/// </summary>
	/// <param name="maxRotateSpeed"></param>
	float GetRotateSpeed(float maxRotateSpeed);


private:


	// 回転速度
	float rotateSpeed_ = 0.0f;
};

