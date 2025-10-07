#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// モデルを読み込む
	modelHandle_ = engine_->LoadModel("./Resources/Models/walk", "walk.gltf");
	modelHandle2_ = engine_->LoadModel("./Resources/Models/sneakWalk", "sneakWalk.gltf");

	// モデルの生成と初期化
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(engine_, camera3d_.get(), modelHandle_);
	model_->worldTransform_->translation_ = Vector3(2.0f, 0.0f, 20.0f);
	model_->worldTransform_->scale_ *= 10.0f;
	model_->material_->enableHalfLambert_ = true;

	// モデルの生成と初期化
	model2_ = std::make_unique<MeshModel>();
	model2_->Initialize(engine_, camera3d_.get(), modelHandle2_);
	model2_->worldTransform_->translation_ = Vector3(-2.0f, 0.0f, 20.0f);
	model2_->worldTransform_->scale_ *= 10.0f;
	model2_->material_->enableHalfLambert_ = true;
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();

	// モデルの更新処理
	model_->Update();
	model2_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// モデルの描画処理
	model_->Draw();
	model2_->Draw();

	// 基底クラスの描画処理
	Scene::Draw();
}