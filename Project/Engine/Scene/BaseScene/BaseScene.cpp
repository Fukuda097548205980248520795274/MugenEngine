#include "BaseScene.h"
#include "MugenEngine.h"


/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void BaseScene::Initialize()
{
	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// メインカメラの生成と初期化
	mainCamera_ = std::make_unique<MainCamera>();
	mainCamera_->Initialize();

	// デバッグカメラの生成と初期化
	debugCamera_ = std::make_unique<DebugCamera>();
	debugCamera_->Initialize();

	// 3Dカメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize();

	// 2Dカメラの生成と初期化
	camera2d_ = std::make_unique<Camera2D>();
	camera2d_->Initialize();

	// シーンマネージャのインスタンスを取得する
	sceneManager_ = SceneManager::GetInstance();
}

/// <summary>
/// 更新処理
/// </summary>
void BaseScene::Update()
{
#ifdef _DEVELOPMENT

	// F1でモード切替
	if (engine_->GetKeyTrigger(DIK_F1))
	{
		if (enableDebug_)
		{
			enableDebug_ = false;
		}
		else
		{
			enableDebug_ = true;
		}
	}

#endif

	// メインカメラの更新処理
	mainCamera_->Update();

	// 2Dカメラの更新処理
	camera2d_->Update();

	// デバッグモード有効
	if (enableDebug_)
	{
		debugCamera_->Update();
		*camera3d_.get() = debugCamera_->GetCamera3D();
	}
	else
	{
		// デバッグモード無効
		*camera3d_.get() = mainCamera_->GetCamera3D();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void BaseScene::Draw()
{

}