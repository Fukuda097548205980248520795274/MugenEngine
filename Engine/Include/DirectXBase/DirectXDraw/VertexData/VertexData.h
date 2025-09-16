#pragma once
#include "../../../Math/Vector2/Vector2.h"
#include "../../../Math/Vector4/Vector4.h"

struct VertexDataModel
{
	// 位置
	Vector4 position;

	// UV座標
	Vector2 texcoord;
};

// スプライトの頂点データ
struct VertexDataSprite
{
	// 位置
	Vector4 position;

	// UV座標
	Vector2 texcoord;
};