#include "Game.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Game::Initialize()
{
	// シーンの生成と初期化
	scene_ = std::make_unique<GameScene>();
	scene_->Initialize(engine_);
}

/// <summary>
/// 更新処理
/// </summary>
void Game::Update()
{
	// シーンの更新処理
	scene_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// シーンの描画処理
	scene_->Draw();
}