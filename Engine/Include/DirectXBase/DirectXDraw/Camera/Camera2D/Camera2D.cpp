#include "Camera2D.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="screenWidth"></param>
/// <param name="screenHeight"></param>
void Camera2D::Initialize(int32_t screenWidth, int32_t screenHeight)
{
	// 引数を受け取る
	screenWidth_ = static_cast<float>(screenWidth);
	screenHeight_ = static_cast<float>(screenHeight);


	// 拡縮
	scale_ = Vector2(1.0f, 1.0f);

	// 回転
	rotation_ = 0.0f;

	// 移動
	translation_ = Vector2(0.0f, 0.0f);


	// ワールド行列
	worldMatrix_ = MakeAffineMatrix(Vector3(scale_.x, scale_.y, 1.0f), Vector3(0.0f, 0.0f, rotation_), Vector3(translation_.x, translation_.y, 0.0f));

	// ビュー行列
	viewMatrix_ = MakeInverseMatrix(worldMatrix_);

	// 正射影行列
	projectionMatrix_ = MakeOrthographicMatrix(0.0f, 0.0f, screenWidth_, screenHeight_, 0.0f, 100.0f);
}

/// <summary>
/// 更新処理
/// </summary>
void Camera2D::Update()
{
	// ワールド行列
	worldMatrix_ = MakeAffineMatrix(Vector3(scale_.x, scale_.y, 1.0f), Vector3(0.0f, 0.0f, rotation_), Vector3(translation_.x, translation_.y, 0.0f));

	// ビュー行列
	viewMatrix_ = MakeInverseMatrix(worldMatrix_);

	// 正射影行列
	projectionMatrix_ = MakeOrthographicMatrix(0.0f, 0.0f, screenWidth_, screenHeight_, 0.0f, 100.0f);
}