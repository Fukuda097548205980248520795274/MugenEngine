#pragma once
#include <cstdint>
#include <vector>

#include "Math/Matrix4x4/Matrix4x4.h"

// 頂点ウェイトデータ
struct VertexWeightData
{
	float weight;
	uint32_t vertexIndex;
};

// ジョイントウェイトデータ
struct JointWeightData
{
	Matrix4x4 inverseBindPoseMatrix;
	std::vector<VertexWeightData> vertexWeights;
};