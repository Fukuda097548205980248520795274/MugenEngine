#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(engine_, camera3d_.get(), Vector3(0.0f, 0.0f, 0.0f));
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();

	// プレイヤーの更新処理
	player_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{

	// プレイヤーの描画処理
	player_->Draw();

	// 基底クラスの描画処理
	Scene::Draw();
}