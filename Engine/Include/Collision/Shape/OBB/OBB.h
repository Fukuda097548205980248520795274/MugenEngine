#pragma once
#include "../../../Math/Vector3/Vector3.h"
#include "../../../Math/Matrix4x4/Matrix4x4.h"

// OBB
struct OBB
{
	// 中心点
	Vector3 center;

	// 回転軸
	Vector3 oriented[3];

	// 大きさ
	Vector3 size;
};