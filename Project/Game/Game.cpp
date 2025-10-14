#include "Game.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Game::Initialize()
{
	// シーンマネージャを取得する
	sceneManager_ = SceneManager::GetInstance();

	// シーンファクトリーを設定する
	sceneManager_->SetSceneFactory(std::make_unique<SceneFactory>());

	// 最初のシーンを指定する
	sceneManager_->SceneTransition("GAME");
}

/// <summary>
/// 更新処理
/// </summary>
void Game::Update()
{
	// シーンの更新処理
	sceneManager_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// シーンの描画処理
	sceneManager_->Draw();
}