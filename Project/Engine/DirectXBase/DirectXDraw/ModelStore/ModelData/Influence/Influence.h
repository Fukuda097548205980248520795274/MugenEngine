#pragma once
#include <cstdint>
#include <array>

#include "Math/Matrix4x4/Matrix4x4.h"

// インフルエンスの最大数
const uint32_t kNumMaxInfluence = 4;

// 頂点インフルエンス
struct VertexInfluence
{
	std::array<float, kNumMaxInfluence> weights;
	std::array<int32_t, kNumMaxInfluence> jointIndices;
};


// GPUに送るウェル
struct WellForGPU
{
	// 位置用
	Matrix4x4 skeletonSpaceMatrix;

	// 法線用
	Matrix4x4 skeletonSpaceInverseTransposeMatrix;
};