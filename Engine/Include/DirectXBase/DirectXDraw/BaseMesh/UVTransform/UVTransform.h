#pragma once
#include "../../../../Math/Matrix4x4/Matrix4x4.h"
#include "../../../../Math/Vector2/Vector2.h"

// UVトランスフォーム
class UVTransform
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	// 拡縮
	Vector2 scale_{};

	// 回転
	float rotation_;

	// 移動
	Vector2 translation_{};

	// アフィン変換行列
	Matrix4x4 affineMatrix_;
};