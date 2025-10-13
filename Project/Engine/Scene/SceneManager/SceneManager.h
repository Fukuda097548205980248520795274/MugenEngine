#pragma once
#include "Scene/BaseScene/BaseScene.h"
#include "Scene/BaseSceneFactory/BaseSceneFactory.h"

class SceneManager
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static SceneManager* GetInstance();

	/// <summary>
	/// シーンファクトリーのSetter
	/// </summary>
	/// <param name="sceneFactory"></param>
	void SetSceneFactory(std::unique_ptr<BaseSceneFactory> sceneFactory);

	/// <summary>
	/// シーン遷移する
	/// </summary>
	/// <param name="scene"></param>
	void SceneTransition(const std::string& sceneName);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();


private:

	/// <summary>
	/// 次のシーンの初期化
	/// </summary>
	void InitializeNextScene();


	// シングルトン
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(SceneManager&) = delete;
	SceneManager& operator=(SceneManager&) = delete;

	// インスタンス
	static SceneManager* instance_;

	// シーン
	std::unique_ptr<BaseScene> scene_ = nullptr;


	// シーン名
	std::string sceneName_{};

	// 遷移フラグ
	bool isTransition_ = false;


	// シーンファクトリー
	std::unique_ptr<BaseSceneFactory> sceneFactory_ = nullptr;
};

