#include "DebugCamera.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void DebugCamera::Initialize()
{
	// 基底クラスの初期化
	GameCamera::Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void DebugCamera::Update()
{
	// マウスホイールを上回転させると、向いている方向にズームイン
	if (engine_->GetMouseWheelUp())
	{
		pointLength_ /= 1.2f;

		// 1以下にならないようにする
		if (pointLength_ < 1.0f)
			pointLength_ = 1.0f;
	}

	// マウスホイールを下回転させると、向いている方向にズームアウト
	if (engine_->GetMouseWheelDown())
	{
		pointLength_ *= 1.2f;
	}

	// LShift + マウスホイールを押して動かすと、向いている方向の左右に移動できる
	if (engine_->GetKeyPress(DIK_LSHIFT) && engine_->GetMouseButtonPress(kMouseButtonCenter))
	{
		// マウスのベクトルと距離を取得し、正規化する
		Vector2 mouseVector = engine_->GetMouseVelocity();
		float mouseVectorLength = Length(mouseVector);
		mouseVector = Normalize(mouseVector);

		// 移動量制御
		const float kSpeedController = mouseVectorLength * 0.01f;

		// 回転行列で進む方向を取得する
		Matrix4x4 rotateMatrix = Make3DRotateMatrix4x4(camera3d_->rotation_);
		Vector3 velocity = TransformNormal({ -mouseVector.x , mouseVector.y , 0.0f }, rotateMatrix);

		// 移動する
		pivotPoint_ += velocity * kSpeedController * (pointLength_ / 10.0f);
	} 
	else if (engine_->GetMouseButtonPress(kMouseButtonCenter))
	{
		// マウスホイールを押して動かすと、向いている方向を回転できる

		// マウスのベクトルと距離を取得し、正規化する
		Vector2 mouseVector = engine_->GetMouseVelocity();
		float mouseVectorLength = Length(mouseVector);
		mouseVector = Normalize(mouseVector);

		// 回転量制御
		const float kSpeedController = mouseVectorLength * 0.001f;

		// 回転量
		Vector2 rotationVelocity = mouseVector * kSpeedController;

		// 回転させる
		camera3d_->rotation_.x += rotationVelocity.y;
		camera3d_->rotation_.y += rotationVelocity.x;
	}


	// 球面座標系の位置を取得する
	camera3d_->translation_ =
		pivotPoint_ + SphericalCoordinate(pointLength_, camera3d_->rotation_.x, -(std::numbers::pi_v<float> / 2.0f) - camera3d_->rotation_.y);


	// 基底クラスの更新処理
	GameCamera::Update();
}