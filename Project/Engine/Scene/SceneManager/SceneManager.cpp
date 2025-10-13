#include "SceneManager.h"
#include "MugenEngine.h"

// インスタンス
std::unique_ptr<SceneManager> SceneManager::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
SceneManager* SceneManager::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = std::make_unique<SceneManager>();
	}
	
	return instance_.get();
}

/// <summary>
/// シーンファクトリーのSetter
/// </summary>
/// <param name="sceneFactory"></param>
void SceneManager::SetSceneFactory(std::unique_ptr<BaseSceneFactory> sceneFactory)
{
	// 譲渡する
	sceneFactory_ = std::move(sceneFactory);
}

/// <summary>
/// シーン遷移する
/// </summary>
/// <param name="scene"></param>
void SceneManager::SceneTransition(const std::string& sceneName)
{
	sceneName_ = sceneName;

	// 遷移準備
	isTransition_ = true;
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
	instance_.reset();
	instance_ = nullptr;
}


/// <summary>
/// 次のシーンの初期化
/// </summary>
void SceneManager::InitializeNextScene()
{
	// 次のシーンがある場合
	if (isTransition_)
	{
		// シーンを譲渡し初期化する
		scene_ = sceneFactory_->CreateScene(sceneName_);
		scene_->Initialize(MugenEngine::GetInstance());

		isTransition_ = false;
	}
}