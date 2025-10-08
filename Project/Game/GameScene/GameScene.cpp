#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// モデルの生成と初期化
	model0_ = std::make_unique<MeshModel>();
	model0_->Initialize(engine_, camera3d_.get(), engine_->LoadModel("./Resources/Models/Character", "Character.gltf"));
	model0_->worldTransform_->translation_.x = -5.0f;
	model0_->material_->enableHalfLambert_ = true;
	model0_->material_->enableSpecular_ = true;
	model0_->material_->enableBlinnPhong_ = true;
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();

	// モデルの更新処理
	model0_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// モデルの描画処理
	model0_->Draw();

	// 基底クラスの描画処理
	Scene::Draw();
}