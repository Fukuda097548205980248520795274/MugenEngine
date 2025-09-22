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

	// スプライトの初期化と生成
	sprite_ = std::make_unique<MeshSprite>();
	sprite_->Initialize(engine_, camera2d_.get(), engine_->LoadTexture("./Resources/Textures/uvChecker.png"));
	sprite_->worldTransform_->scale_ = Vector2(256.0f, 256.0f);

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

	if (!engine_->IsAudioPlay(playHandle_) || playHandle_ == 0)
	{
		playHandle_ = engine_->PlayAudio(soundHandle_, 0.5f);
	}

	ImGui::Begin("sprite");
	ImGui::DragFloat2("uvTransform", &sprite_->uvTransform_->translation_.x, 0.1f);
	ImGui::ColorEdit4("color", &sprite_->color_.x);
	ImGui::End();

	// スプライトの更新処理
	sprite_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// スプライトの描画
	sprite_->Draw();
}