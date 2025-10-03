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
	modelHandle1_ = engine_->LoadModel("./Resources/Models/suzanneUV", "suzanneUV.obj");
	modelHandle2_ = engine_->LoadModel("./Resources/Models/node", "node.gltf");

	// モデルの生成と初期化
	model1_ = std::make_unique<MeshModel>();
	model1_->Initialize(engine_, camera3d_.get(), modelHandle1_);
	model1_->worldTransform_->translation_ = Vector3(-5.0f, 0.0f, 30.0f);
	model1_->material_->enableHalfLambert_ = true;
	model1_->material_->enableSpecular_ = true;
	model1_->material_->enableBlinnPhong_ = true;
	model1_->material_->shininess_ = 30.0f;

	model2_ = std::make_unique<MeshModel>();
	model2_->Initialize(engine_, camera3d_.get(), modelHandle2_);
	model2_->worldTransform_->translation_ = Vector3(5.0f, 0.0f, 30.0f);
	model2_->material_->enableHalfLambert_ = true;
	model2_->material_->enableSpecular_ = true;
	model2_->material_->enableBlinnPhong_ = true;
	model2_->material_->shininess_ = 30.0f;
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// 基底クラスの更新処理
	Scene::Update();

	model1_->worldTransform_->rotation_.x += 0.01f;
	model1_->worldTransform_->rotation_.y += 0.01f;

	model2_->worldTransform_->rotation_.z += 0.01f;
	model2_->worldTransform_->rotation_.y += 0.01f;

	timer_ += engine_->GetDeltaTime();

	if (timer_ <= 1.0f)
	{
		model2_->SetModelHandle(modelHandle1_);
	}
	else if (timer_ <= 2.0f)
	{
		model2_->SetModelHandle(modelHandle2_);
	}
	else
	{
		timer_ = 0.0f;
	}

	// モデルの更新処理
	model1_->Update();
	model2_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	// モデルの描画処理
	model1_->Draw();
	model2_->Draw();


	// 基底クラスの描画処理
	Scene::Draw();
}