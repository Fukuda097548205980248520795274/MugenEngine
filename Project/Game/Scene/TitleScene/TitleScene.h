#pragma once
#include "MugenEngine.h"

#include "../GameScene/BaseCharacter/Player/Player.h"

class TitleScene : public BaseScene
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;


private:

	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;
};

