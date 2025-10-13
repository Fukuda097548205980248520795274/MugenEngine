#include "MainCamera.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void MainCamera::Initialize()
{
	// 基底クラスを初期化
	GameCamera::Initialize();

	// 初期値を小さくする
	pointLength_ = 1.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void MainCamera::Update()
{
	// 長さが最小値を越えないようにする
	pointLength_ = std::max(1.0f, pointLength_);

	// 回転の値を渡す
	camera3d_->rotation_ = pointRotation_;

	// 球面座標系の位置
	camera3d_->translation_ =
		pivotPoint_ + SphericalCoordinate(pointLength_, camera3d_->rotation_.x, -(std::numbers::pi_v<float> / 2.0f) - camera3d_->rotation_.y);

	// 基底クラスの更新処理
	GameCamera::Update();
}