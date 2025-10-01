#include "GameCamera.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void GameCamera::Initialize(const MugenEngine* engine)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;

	// 3Dカメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(engine_->GetScreenWidth(), engine_->GetScreenHeight());
}

/// <summary>
/// 更新処理
/// </summary>
void GameCamera::Update()
{
	// 3Dカメラの更新
	camera3d_->Update();
}