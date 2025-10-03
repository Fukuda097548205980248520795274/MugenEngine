#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);

	modelHandle_ = engine_->LoadModel("./Resources/Models/AnimationCube", "AnimationCube.gltf");

	// モデルの生成と初期化
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(engine_,camera3d_.get(), modelHandle_);
	model_->worldTransform_->translation_ = Vector3(0.0f , -5.0f , 30.0f);
	model_->material_->enableHalfLambert_ = true;
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
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// モデルの描画処理
	model_->Draw();

	// 基底クラスの描画処理
	Scene::Draw();
}