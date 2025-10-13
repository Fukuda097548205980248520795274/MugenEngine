#include "GameCamera.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void GameCamera::Initialize()
{
	// インスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// 3Dカメラの生成と初期化
	camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void GameCamera::Update()
{
	// 3Dカメラの更新
	camera3d_->Update();
}