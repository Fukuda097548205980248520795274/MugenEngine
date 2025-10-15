#include "Enemy.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="camera3d"></param>
/// <param name="startPosition"></param>
void Enemy::Initialize(const Camera3D* camera3d, const Vector3& startPosition)
{
	// 基底クラスの初期化
	BaseCharacter::Initialize(camera3d, startPosition);

	// モデルの生成と初期化
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(camera3d_, engine_->LoadModel("./Resources/Models/characterBox", "characterBox.obj"));
	model_->SetParent(worldTransform_.get());

	// 赤色にする
	Material* material = model_->GetMateril("立方体");
	material->color_ = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
}

/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
	// 基底クラスの更新処理
	BaseCharacter::Update();

	model_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw()
{
	// モデルの描画処理
	model_->Draw();
}