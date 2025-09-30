#pragma once
#include "../../../../Math/Vector2/Vector2.h"
#include "../../../../Math/Vector3/Vector3.h"
#include "../../../../Math/Vector4/Vector4.h"

// GPUに送るモデル用の頂点データ
struct VertexDataForGPU
{
	// 位置
	Vector4 position;

	// UV座標
	Vector2 texcoord;

	// 法線
	Vector3 normal;
};