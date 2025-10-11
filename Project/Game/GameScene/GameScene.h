#pragma once
#include "MugenEngine.h"

#include "BaseCharacter/Player/Player.h"

class GameScene : public Scene
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


public:

	
	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;


	// パーティクルエミッター
	std::unique_ptr<BillboardParticleEmitter> particleEmitter_ = nullptr;


	// サウンドハンドル
	SoundHandle soundHandle_{};

	// プレイハンドル
	PlayHandle playHandle_{};


	// テクスチャハンドル
	TextureHandle textureHandle_{};
};

