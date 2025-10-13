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


	// パーティクルエミッター
	std::unique_ptr<BillboardParticleEmitter> billboardParticleEmitter_ = nullptr;
	std::unique_ptr<ModelParticleEmitter> modelParticleEmitter_ = nullptr;


	// サウンドハンドル
	SoundHandle soundHandle_{};

	// プレイハンドル
	PlayHandle playHandle_{};


	// テクスチャハンドル
	TextureHandle textureHandle_{};

	// モデルハンドル
	ModelHandle modelHandle_{};
};

