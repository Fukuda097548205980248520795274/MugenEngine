#include "Scene.h"
#include "MugenEngine.h"


/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Scene::Initialize(const MugenEngine* engine)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;

	// メインカメラの生成と初期化
	mainCamera_ = std::make_unique<MainCamera>();
	mainCamera_->Initialize(engine_);

	// デバッグカメラの生成と初期化
	debugCamera_ = std::make_unique<DebugCamera>();
	debugCamera_->Initialize(engine_);

	// 3Dカメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());

	// 2Dカメラの生成と初期化
	camera2d_ = std::make_unique<Camera2D>();
	camera2d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());
}

/// <summary>
/// 更新処理
/// </summary>
void Scene::Update()
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
void Scene::Draw()
{

}