#pragma once
#include "../../../../Math/Vector4/Vector4.h"
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

// GPUに送るモデル用のマテリアルデータ
struct MaterialDataForGPU
{
	// 色
	Vector4 color_;

	// ライティング有効化
	int32_t enableLighting_;

	// ハーフランバート有効化
	int32_t enableHalfLambert_;

	// スペキュラー有効化
	int32_t enableSpecular_;

	// 光沢度
	float shininess_;

	// UVトランスフォーム
	Matrix4x4 uvTransform_;
};