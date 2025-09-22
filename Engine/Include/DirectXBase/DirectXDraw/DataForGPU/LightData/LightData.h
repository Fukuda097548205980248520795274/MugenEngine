#pragma once
#include "../../../../Math/Vector4/Vector4.h"
#include "../../../../Math/Vector3/Vector3.h"

// GPUに送る平行光源データ
struct DirectionalLightForGPU
{
	// 色
	Vector4 color;

	// 向き
	Vector3 direction;

	// 輝度
	float intensity;
};