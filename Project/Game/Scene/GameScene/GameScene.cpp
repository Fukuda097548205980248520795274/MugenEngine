#include "GameScene.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void GameScene::Initialize()
{
	// 基底クラスの初期化
	BaseScene::Initialize();

	mainCamera_->pointLength_ = 12.0f;


	// 平面の生成と初期化
	plane_ = std::make_unique<MeshPlane>();
	plane_->Initialize(camera3d_.get(), engine_->LoadTexture("./Resources/Textures/ground/ground.png"));
	plane_->worldTransform_->scale_ *= 20.0f;
	plane_->uvTransform_->scale_ *= 20.0f;

	// プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(camera3d_.get(), Vector3(0.0f, 0.0f, 0.0f));

	// 敵の生成と初期化
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(camera3d_.get(), Vector3(0.0f, 0.0f, 10.0f));


	// メインカメラ回転コントローラの生成と初期化
	mainCameraRotateController_ = std::make_unique<MainCameraRotateController>();
	mainCameraRotateController_->Initialize();


	// サウンドハンドル
	soundHandle_ = engine_->LoadAudio("./Resources/Sounds/bgm/forget_me_not.mp3");
}

/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update()
{
	// メインカメラがプレイヤーを追従するようにする
	Vector3 mainCameraOffset = Vector3(0.0f, 1.7f, 0.0f);
	mainCamera_->pivotPoint_ = player_->GetWorldPosition() + mainCameraOffset;

	// メインカメラ回転を取得し加算する
	mainCamera_->pointRotation_ += mainCameraRotateController_->GetRotateValue();


	// 基底クラスの更新処理
	BaseScene::Update();

	// 平面の更新処理
	plane_->Update();

	// プレイヤーの更新処理
	player_->Update();

	// 敵の更新処理
	enemy_->Update();


	// ループ再生
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
	// 平面の描画処理
	plane_->Draw();

	// プレイヤーの描画処理
	player_->Draw();

	// 敵の描画処理
	enemy_->Draw();

	// 基底クラスの描画処理
	BaseScene::Draw();
}