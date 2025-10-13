#include "SceneManager.h"
#include "MugenEngine.h"

// インスタンス
SceneManager* SceneManager::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
SceneManager* SceneManager::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	
	return instance_;
}

/// <summary>
/// 更新処理
/// </summary>
void SceneManager::Update()
{
	// 次のシーンの初期化
	InitializeNextScene();

	// シーンの更新
	scene_->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Draw()
{
	// シーンの描画
	scene_->Draw();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
	// インスタンスの削除
	delete instance_;
	instance_ = nullptr;
}


/// <summary>
/// 次のシーンの初期化
/// </summary>
void SceneManager::InitializeNextScene()
{
	// 次のシーンがある場合
	if (nextScene_)
	{
		// シーンを譲渡し初期化する
		scene_ = std::move(nextScene_);
		scene_->Initialize(MugenEngine::GetInstance());

		nextScene_ = nullptr;
	}
}