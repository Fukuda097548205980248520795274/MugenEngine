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

	// カメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());
	camera3d_->translation_.z = -20.0f;

	// 立方体の初期化と生成
	cube_ = std::make_unique<MeshCube>();
	cube_->Initialize(engine_, camera3d_.get(), engine_->LoadTexture("./Resources/Textures/uvChecker.png"));
	cube_->enableHalfLambert_ = true;

	// BGMを読み込む
	soundHandle_ = engine_->LoadAudio("./Resources/Sounds/bgm/Tukiyo_Ni_Ukabu_Tensyukaku.mp3");
}

/// <summary>
/// 更新処理
/// </summary>
void Game::Update()
{
	// カメラの更新処理
	camera3d_->Update();

	if (!engine_->IsAudioPlay(playHandle_) || playHandle_ == 0)
	{
		playHandle_ = engine_->PlayAudio(soundHandle_, 0.5f);
	}

	// 立方体の更新処理
	cube_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// 立方体の描画
	cube_->Draw();
}