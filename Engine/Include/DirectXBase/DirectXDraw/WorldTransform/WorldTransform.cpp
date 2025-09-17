#include "WorldTransform.h"

/// <summary>
/// 初期化
/// </summary>
void WorldTransform3D::Initialize()
{
	// 拡縮
	scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// 回転
	rotation_ = Vector3(0.0f, 0.0f, 0.0f);

	// 移動
	translation_ = Vector3(0.0f, 0.0f, 0.0f);

	// ワールド行列
	worldMatrix_ = MakeAffineMatrix(scale_, rotation_, translation_);
}

/// <summary>
/// 更新処理
/// </summary>
void WorldTransform3D::Update()
{
	// ワールド行列
	worldMatrix_ = MakeAffineMatrix(scale_, rotation_, translation_);

	// 親がいたら、親子構造の乗算を行う
	if (parent_ != nullptr)
	{
		worldMatrix_ = worldMatrix_ * (*parent_);
	}
}

/// <summary>
/// ワールド座標のGetter
/// </summary>
/// <returns></returns>
Vector3 WorldTransform3D::GetWorldPosition() const
{
	// ワールド座標
	Vector3 worldPosition;

	worldPosition.x = worldMatrix_.m[3][0];
	worldPosition.y = worldMatrix_.m[3][1];
	worldPosition.z = worldMatrix_.m[3][2];

	return worldPosition;
}







/// <summary>
/// 初期化
/// </summary>
void WorldTransform2D::Initialize()
{
	// 拡縮
	scale_ = Vector2(1.0f, 1.0f);

	// 回転
	rotation_ = 0.0f;

	// 移動
	translation_ = Vector2(0.0f, 0.0f);

	// ワールド行列
	worldMatrix_ = MakeAffineMatrix(Vector3(scale_.x, scale_.y, 0.0f), Vector3(0.0f, 0.0f, rotation_), Vector3(translation_.x, translation_.y, 0.0f));
}

/// <summary>
/// 更新処理
/// </summary>
void WorldTransform2D::Update()
{
	// ワールド行列
	worldMatrix_ = MakeAffineMatrix(Vector3(scale_.x, scale_.y, 0.0f), Vector3(0.0f, 0.0f, rotation_), Vector3(translation_.x, translation_.y, 0.0f));

	// 親がいたら、親子構造の乗算を行う
	if (parent_ != nullptr)
	{
		worldMatrix_ = worldMatrix_ * (*parent_);
	}
}

/// <summary>
/// ワールド座標のGetter
/// </summary>
/// <returns></returns>
Vector3 WorldTransform2D::GetWorldPosition() const
{
	// ワールド座標
	Vector3 worldPosition;

	worldPosition.x = worldMatrix_.m[3][0];
	worldPosition.y = worldMatrix_.m[3][1];
	worldPosition.z = worldMatrix_.m[3][2];

	return worldPosition;
}