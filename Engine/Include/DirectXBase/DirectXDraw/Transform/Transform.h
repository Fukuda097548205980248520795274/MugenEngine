#pragma once
#include "../../../Math/Vector2/Vector2.h"
#include "../../../Math/Vector3/Vector3.h"

// 2Dトランスフォーム
struct Transform2D
{
	// 拡縮
	Vector2 scale;

	// 回転
	float rotation;

	// 移動
	Vector2 translation;
};

// 3Dトランスフォーム
struct Transform3D
{
	// 拡縮
	Vector3 scale;

	// 回転
	Vector3 rotation;

	// 移動
	Vector3 translation;
};