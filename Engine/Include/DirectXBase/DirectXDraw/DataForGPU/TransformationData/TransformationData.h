#pragma once
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

// モデル用の座標変換データ
struct TransformationDataModel
{
	// ワールドビュープロジェクション行列
	Matrix4x4 worldViewProjection;

	// ワールド行列
	Matrix4x4 world;
};