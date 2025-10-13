#pragma once
#include <string>
#include "Scene/BaseScene/BaseScene.h"

class BaseSceneFactory
{
public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~BaseSceneFactory() = default;

	/// <summary>
	/// 名前を指定してシーンを生成する
	/// </summary>
	virtual std::unique_ptr<BaseScene> CreateScene(const std::string& sceneName) = 0;
};

