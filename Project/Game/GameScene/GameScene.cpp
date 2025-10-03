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
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/uvChecker.png");

	// スプライトの生成と初期化
	sprite_ = std::make_unique<MeshSprite>();
	sprite_->Initialize(engine_, camera2d_.get(), textureHandle_);
	sprite_->worldTransform_->translation_ = Vector3(300.0f, 300.0f, 0.0f);
	sprite_->worldTransform_->scale_ = Vector2(128.0f, 128.0f);
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();


	// スプライトの更新処理
	sprite_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// スプライトの描画処理
	sprite_->Draw();


	// 基底クラスの描画処理
	Scene::Draw();
}