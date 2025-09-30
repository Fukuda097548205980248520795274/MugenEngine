#include "UVTransform.h"

/// <summary>
/// 初期化
/// </summary>
void UVTransform::Initialize()
{
	// 拡縮
	scale_ = Vector2(1.0f, 1.0f);

	// 回転
	rotation_ = 0.0f;

	// 移動
	translation_ = Vector2(0.0f, 0.0f);

	// アフィン変換行列
	affineMatrix_ = MakeAffineMatrix(Vector3(scale_.x, scale_.y, 0.0f), Vector3(0.0f, 0.0f, rotation_), Vector3(translation_.x, translation_.y, 0.0f));
}

/// <summary>
/// 更新処理
/// </summary>
void UVTransform::Update()
{
	// アフィン変換行列
	affineMatrix_ = MakeAffineMatrix(Vector3(scale_.x, scale_.y, 0.0f), Vector3(0.0f, 0.0f, rotation_), Vector3(translation_.x, translation_.y, 0.0f));
}