#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// テクスチャハンドル
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/white2x2.png");

	// UV球の初期化と生成
	uvSphere_ = std::make_unique<MeshUVSphere>();
	uvSphere_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere_->worldTransform_->translation_.z = 35.0f;
	uvSphere_->material_->enableHalfLambert_ = true;
	uvSphere_->material_->enableSpecular_ = true;
	uvSphere_->material_->enableBlinnPhong_ = true;
	uvSphere_->material_->shininess_ = 50.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();


	if (engine_->GetKeyPress(DIK_W))
		uvSphere_->worldTransform_->translation_.y += 0.1f;

	if (engine_->GetKeyPress(DIK_A))
		uvSphere_->worldTransform_->translation_.x -= 0.1f;

	if (engine_->GetKeyPress(DIK_S))
		uvSphere_->worldTransform_->translation_.y -= 0.1f;

	if (engine_->GetKeyPress(DIK_D))
		uvSphere_->worldTransform_->translation_.x += 0.1f;

	if (engine_->IsGamepadEnable(0))
	{

	}

	// UV球の更新処理
	uvSphere_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{

	// UV球の描画処理
	uvSphere_->Draw();


	// 基底クラスの描画処理
	Scene::Draw();
}