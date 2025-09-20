#pragma once
#include "../../../../Math/Vector4/Vector4.h"
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

// モデル用のマテリアルデータ
struct MaterialDataModel
{
	// 色
	Vector4 color_;

	// ライティング有効化
	int32_t enableLighting_;

	// ハーフランバート有効化
	int32_t enableHalfLambert_;

	float padding[2];

	// UVトランスフォーム
	Matrix4x4 uvTransform_;
};