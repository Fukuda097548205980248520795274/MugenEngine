#pragma once
#include "MugenEngine.h"

#include "BaseCharacter/Player/Player.h"

class GameScene : public BaseScene
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;


public:

	
	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;


	// テクスチャハンドル
	TextureHandle textureHandle_{};

	// パーティクルエミッター
	std::unique_ptr<BillboardParticleEmitter> billboardParticleEmitter_ = nullptr;



	// サウンドハンドル
	SoundHandle soundHandle_{};

	// プレイハンドル
	PlayHandle playHandle_{};
};

