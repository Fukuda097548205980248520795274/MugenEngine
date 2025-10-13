#pragma once
#include "GameCamera/GameCamera.h"

class DebugCamera : public GameCamera
{
public:


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
};

