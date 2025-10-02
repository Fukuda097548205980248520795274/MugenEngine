#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);

	// テクスチャハンドル
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/white2x2.png");

	// UV球の初期化と生成
	uvSphere1_ = std::make_unique<MeshUVSphere>();
	uvSphere1_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere1_->material_->enableHalfLambert_ = true;
	uvSphere1_->material_->enableSpecular_ = true;
	uvSphere1_->material_->enableBlinnPhong_ = true;
	uvSphere1_->material_->shininess_ = 50.0f;

	// UV球の初期化と生成
	uvSphere2_ = std::make_unique<MeshUVSphere>();
	uvSphere2_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere2_->material_->enableHalfLambert_ = true;
	uvSphere2_->material_->enableSpecular_ = true;
	uvSphere2_->material_->enableBlinnPhong_ = true;
	uvSphere2_->material_->shininess_ = 50.0f;
	uvSphere2_->worldTransform_->translation_.x = 30.0f;


	// BGMを読み込む
	soundHandle_ = engine_->LoadAudio("./Resources/Sounds/bgm/forget_me_not.mp3");
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();


	// 音楽ループ
	if (!engine_->IsAudioPlay(playHandle_) || playHandle_ == 0)
	{
		playHandle_ = engine_->PlayAudio(soundHandle_, 0.5f);
	}


	// UV球の更新処理
	uvSphere1_->Update();
	uvSphere2_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// UV球の描画処理
	uvSphere1_->Draw();
	uvSphere2_->Draw();


	// 基底クラスの描画処理
	Scene::Draw();
}