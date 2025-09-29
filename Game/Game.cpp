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

	// モデルの初期化と生成
	uvSphere_ = std::make_unique<MeshUVSphere>();
	uvSphere_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere_->material_->enableSpecular_ = true;
	uvSphere_->material_->enableBlinnPhong_ = true;

	// BGMを読み込む
	soundHandle_ = engine_->LoadAudio("./Resources/Sounds/bgm/forget_me_not.mp3");
}

/// <summary>
/// 更新処理
/// </summary>
void Game::Update()
{
	ImGui::Begin("Camera");
	ImGui::DragFloat3("rotation", &camera3d_->rotation_.x, 0.01f);
	ImGui::DragFloat3("translation", &camera3d_->translation_.x, 0.1f);
	ImGui::End();

	ImGui::Begin("UVSphere");
	ImGui::DragFloat3("scale", &uvSphere_->worldTransform_->scale_.x, 0.01f);
	ImGui::End();


	// カメラの更新処理
	camera3d_->Update();
	camera2d_->Update();

	if (!engine_->IsAudioPlay(playHandle_) || playHandle_ == 0)
	{
		playHandle_ = engine_->PlayAudio(soundHandle_, 0.5f);
	}

	// モデルの更新処理
	uvSphere_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// モデルの描画
	uvSphere_->Draw();
}