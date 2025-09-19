#pragma once
#include "../../../Math/Vector3/Vector3.h"
#include "../../../Math/Matrix3x3/Matrix3x3.h"

// OBB
struct OBB
{
	// 中心点
	Vector3 center;

	// 回転軸
	Matrix3x3 oriented;

	// 大きさ
	Vector3 size;
};