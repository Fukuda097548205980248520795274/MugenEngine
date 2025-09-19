#pragma once
#include "../../../Math/Vector3/Vector3.h"

// 平面
struct Plane
{
	// 法線
	Vector3 normal;

	// 距離
	float distance;
};