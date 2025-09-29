#pragma once
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

// GPUに送るモデル用の座標変換データ
struct TransformationDataForGPU
{
	// ワールドビュープロジェクション行列
	Matrix4x4 worldViewProjection;

	// ワールド行列
	Matrix4x4 world;

	// ワールド行列の逆転置行列
	Matrix4x4 worldInverseTranspose;
};