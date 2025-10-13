#pragma once
#include "Scene/BaseScene/BaseScene.h"

class SceneManager
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static SceneManager* GetInstance();

	/// <summary>
	/// シーン遷移する
	/// </summary>
	/// <param name="scene"></param>
	void SceneTransition(std::unique_ptr<BaseScene> scene) { nextScene_ = std::move(scene); }

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

	// 次のシーン
	std::unique_ptr<BaseScene> nextScene_ = nullptr;
};

