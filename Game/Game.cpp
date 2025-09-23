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

	// パーティクルエミッターの生成と初期化
	particleEmitterType_ = std::make_unique<ParticleEmitter>();
	particleEmitterType_->Initialize(engine_, camera3d_.get(), "Particle", 20, Vector3(0.0f, 0.0f, 0.0f), 1, 0.5f);

	phParticleEmitter_ = engine_->LoadParticle(particleEmitterType_.get());
	particleEmitter_ = engine_->GetParticleEmitter(phParticleEmitter_);

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

	// 放出
	particleEmitter_->Emit();

	// スプライトの更新処理
	particleEmitter_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Game::Draw()
{
	// スプライトの描画
	particleEmitter_->Draw();
}