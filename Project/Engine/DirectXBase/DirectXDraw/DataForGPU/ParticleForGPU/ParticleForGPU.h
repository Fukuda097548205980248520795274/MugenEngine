#pragma once
#include "Math/Matrix4x4/Matrix4x4.h"

struct ParticleForGPU
{
	// ワールドビュープロジェクション行列
	Matrix4x4 worldViewProjectionMatrix;

	// ワールド行列
	Matrix4x4 world;

	// 色
	Vector4 color;
};