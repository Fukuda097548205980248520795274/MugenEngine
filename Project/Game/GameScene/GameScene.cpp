#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);

	mainCamera_->pivotPoint_ = Vector3(0.0f, 0.0f, -30.0f);

	// プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(engine_, camera3d_.get(), Vector3(0.0f, 0.0f, 0.0f));

	// サウンドハンドル
	soundHandle_ = engine_->LoadAudio("./Resources/Sounds/bgm/forget_me_not.mp3");


	// テクスチャを読み込む
	textureHandle0_ = engine_->LoadTexture("./Resources/Textures/uvChecker.png");
	textureHandle1_ = engine_->LoadTexture("./Resources/Textures/circle.png");

	// ビルボードパーティクルエミッター
	billboardParticleEmitter_ = std::make_unique<BillboardParticleEmitter>();
	billboardParticleEmitter_->Initliaze(engine_, camera3d_.get(), 100, textureHandle0_, "testParticle_0");


	// モデルを読み込む
	modelHandle_ = engine_->LoadModel("./Resources/Models/suzanne", "suzanne.obj");

	// モデルパーティクルエミッターの生成と初期化
	modelParticleEmitter_ = std::make_unique<ModelParticleEmitter>();
	modelParticleEmitter_->Initliaze(engine_, camera3d_.get(), 100, modelHandle_, "testParticle_1");
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
#ifdef _DEVELOPMENT
	ImGui::Begin("Camera");
	ImGui::DragFloat3("pivotPoint", &mainCamera_->pivotPoint_.x, 0.1f);
	ImGui::End();
#endif

	// 基底クラスの更新処理
	Scene::Update();

	// プレイヤーの更新処理
	player_->Update();



	if (rand() % 10 > 2)
	{
		billboardParticleEmitter_->SetTextureHandle(textureHandle0_);
	}
	else
	{
		billboardParticleEmitter_->SetTextureHandle(textureHandle1_);
	}

	// パーティクルの更新処理
	billboardParticleEmitter_->Update();
	modelParticleEmitter_->Update();


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
	modelParticleEmitter_->Draw();

	// 基底クラスの描画処理
	Scene::Draw();
}