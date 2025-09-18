#pragma once
#include "../../../Math/Vector4/Vector4.h"

// モデル用のマテリアルデータ
struct MaterialDataModel
{
	// 色
	Vector4 color_;

	// ライティング有効化
	int32_t enableLighting_;
};