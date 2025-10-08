#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// 平面の初期化
	plane_ = std::make_unique<MeshPlane>();
	plane_->Initialize(engine_, camera3d_.get(), engine_->LoadTexture("./Resources/Textures/uvChecker.png"));
	plane_->material_->enableHalfLambert_ = true;
	plane_->material_->enableSpecular_ = true;
	plane_->material_->enableBlinnPhong_ = true;
	plane_->worldTransform_->scale_ = Vector3(256.0f, 1.0f, 256.0f);

}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();

	// 平面の更新処理
	plane_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// 平面の描画処理
	plane_->Draw();

	// 基底クラスの描画処理
	Scene::Draw();
}