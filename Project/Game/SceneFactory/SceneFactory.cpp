#include "SceneFactory.h"
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/GameScene/GameScene.h"

/// <summary>
/// 名前を指定してシーンを生成する
/// </summary>
std::unique_ptr<BaseScene> SceneFactory::CreateScene(const std::string& sceneName)
{
	// タイトル
	if (sceneName == "TITLE")
	{
		return std::make_unique<TitleScene>();
	}

	// ゲーム
	if (sceneName == "GAME")
	{
		return std::make_unique<GameScene>();
	}

	assert(false);
	return nullptr;
}