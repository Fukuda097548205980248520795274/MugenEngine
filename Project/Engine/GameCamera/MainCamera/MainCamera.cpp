#include "MainCamera.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void MainCamera::Initialize(const MugenEngine* engine)
{
	// 基底クラスを初期化
	GameCamera::Initialize(engine);
}

/// <summary>
/// 更新処理
/// </summary>
void MainCamera::Update()
{
	// 基底クラスの更新処理
	GameCamera::Update();
}