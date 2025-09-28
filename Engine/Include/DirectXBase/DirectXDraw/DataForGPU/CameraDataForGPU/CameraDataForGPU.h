#pragma once
#include "../../../../Math/Vector3/Vector3.h"

// GPUに送るカメラデータ
struct CameraDataForGPU
{
	// ワールド座標
	Vector3 worldPosition;
};