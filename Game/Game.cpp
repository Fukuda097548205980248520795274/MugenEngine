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


	// モデルハンドル
	modelHandle_ = engine_->LoadModel("./Resources/Models/node", "node.gltf");

	// モデルの初期化と生成
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(engine_, camera3d_.get(), modelHandle_);
	model_->enableHalfLambert_ = true;

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

	ImGui::Begin("Model");
	ImGui::DragFloat3("rotation", &model_->worldTransform_->rotation_.x, 0.01f);
	ImGui::DragFloat2("uvTransform", &model_->uvTransform_->translation_.x, 0.1f);
	ImGui::End();

	if (!engine_->IsAudioPlay(playHandle_) || playHandle_ == 0)
	{
		playHandle_ = engine_->PlayAudio(soundHandle_, 0.5f);
	}

	// モデルの更新処理
	model_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// モデルの描画
	model_->Draw();
}