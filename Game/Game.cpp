#include "Game.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Game::Initialize(const MugenEngine* engine)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;


	// ワールドトランスフォームの生成と初期化
	worldTransform_ = std::make_unique<WorldTransform3D>();
	worldTransform_->Initialize();

	// UVトランスフォームの生成と初期化
	uvTransform_ = std::make_unique<UVTransform>();
	uvTransform_->Initialize();

	// カメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());
	camera3d_->translation_.z = -20.0f;

	// テクスチャを読み込む
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/white2x2.png");
}

/// <summary>
/// 更新処理
/// </summary>
void Game::Update()
{
	// 更新
	worldTransform_->Update();
	uvTransform_->Update();
	camera3d_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	engine_->DrawCube(worldTransform_.get(), uvTransform_.get(), camera3d_.get(), textureHandle_);
}