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

	// 3Dカメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());
	camera3d_->translation_.z = -20.0f;

	// 2Dカメラの生成と初期化
	camera2d_ = std::make_unique<Camera2D>();
	camera2d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());


	// テクスチャを読み込む
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/white2x2.png");

	// UV球の初期化と生成
	uvSphere_ = std::make_unique<MeshUVSphere>();
	uvSphere_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere_->enableHalfLambert_ = true;
	uvSphere_->color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

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
	camera2d_->Update();

	ImGui::Begin("UVSphere");
	ImGui::DragFloat3("translation", &uvSphere_->worldTransform_->translation_.x, 0.1f);
	ImGui::End();

	if (!engine_->IsAudioPlay(playHandle_) || playHandle_ == 0)
	{
		playHandle_ = engine_->PlayAudio(soundHandle_, 0.5f);
	}

	// UV球の更新処理
	uvSphere_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// UV球の描画
	uvSphere_->Draw();
}