#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// テクスチャを読み込む
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/uvChecker.png");

	// UV球の生成と初期化
	uvSphere_ = std::make_unique<MeshUVSphere>();
	uvSphere_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere_->worldTransform_->translation_.z = 20.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();

	//  UV球の更新処理
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