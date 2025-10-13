#pragma once
#include "MugenEngine.h"


class SceneFactory : public BaseSceneFactory
{
public:

	/// <summary>
	/// 名前を指定してシーンを生成する
	/// </summary>
	std::unique_ptr<BaseScene> CreateScene(const std::string& sceneName) override;
};

