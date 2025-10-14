#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize()
{
	// 基底クラスの初期化
	BaseScene::Initialize();

	mainCamera_->pivotPoint_.z = -20.0f;

	// プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(camera3d_.get(), Vector3(0.0f, 0.0f, 0.0f));

	// サウンドハンドル
	soundHandle_ = engine_->LoadAudio("./Resources/Sounds/bgm/forget_me_not.mp3");


	// テクスチャを読み込む
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/circle.png");

	// ビルボードパーティクルエミッター
	billboardParticleEmitter_ = std::make_unique<BillboardParticleEmitter>();
	billboardParticleEmitter_->Initliaze(camera3d_.get(), 100, textureHandle_, "testParticle_0");
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	BaseScene::Update();

	// プレイヤーの更新処理
	player_->Update();


	// パーティクルの更新処理
	billboardParticleEmitter_->Update();

	//ループ再生
	if (!engine_->IsAudioPlay(playHandle_) || playHandle_.IsUse())
	{
		playHandle_ =  engine_->PlayAudio(soundHandle_ , 0.3f);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// プレイヤーの描画処理
	player_->Draw();

	// パーティクルの描画処理
	billboardParticleEmitter_->Draw();

	// 基底クラスの描画処理
	BaseScene::Draw();
}