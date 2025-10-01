#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize(const MugenEngine* engine)
{
	// 基底クラスの初期化
	Scene::Initialize(engine);


	// モデルを読み込む
	modelHandle_ = engine_->LoadModel("./Resources/Models/terrain", "terrain.obj");

	// モデルの初期化と生成
	model_ = std::make_unique<MeshModel>();
	model_->Initialize(engine_, camera3d_.get(), modelHandle_);
	model_->material_->enableHalfLambert_ = true;
	model_->material_->enableSpecular_ = true;
	model_->material_->enableBlinnPhong_ = true;
	model_->material_->shininess_ = 50.0f;



	// テクスチャハンドル
	textureHandle_ = engine_->LoadTexture("./Resources/Textures/white2x2.png");

	// UV球の初期化と生成
	uvSphere_ = std::make_unique<MeshUVSphere>();
	uvSphere_->Initialize(engine_, camera3d_.get(), textureHandle_);
	uvSphere_->material_->enableHalfLambert_ = true;
	uvSphere_->material_->enableSpecular_ = true;
	uvSphere_->material_->enableBlinnPhong_ = true;
	uvSphere_->material_->shininess_ = 50.0f;


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

	uint32_t a = Combination(5,1);

	// モデルの更新処理
	model_->Update();

	// UV球の更新処理
	uvSphere_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// モデルの描画
	model_->Draw();

	// UV球の描画処理
	uvSphere_->Draw();


	// 基底クラスの描画処理
	Scene::Draw();
}