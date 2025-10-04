#pragma once
#include "Math/Vector2/Vector2.h"
#include "Math/Vector3/Vector3.h"
#include "Math/Quaternion/Quaternion.h"

// オイラー角のトランスフォーム
struct EulerTransform
{
	// 拡縮
	Vector3 scale;

	// 回転
	Vector3 rotate;

	// 移動
	Vector3 translate;
};

// クォータニオンのトランスフォーム
struct QuaternionTransform
{
	// 拡縮
	Vector3 scale;

	// 回転
	Quaternion rotate;

	// 移動
	Vector3 translate;
};