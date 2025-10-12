#include "BillboardParticleEmitter.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="numMaxParticle"></param>
void BillboardParticleEmitter::Initliaze(const MugenEngine* engine, const Camera3D* camera3d, uint32_t numMaxParticle,TextureHandle textureHandle, const std::string& name)
{
	// nullptrチェック
	assert(engine);
	assert(camera3d);

	// 引数を受け取る
	engine_ = engine;
	camera3d_ = camera3d;
	numMaxParticle_ = numMaxParticle;
	textureHandle_ = textureHandle;
	name_ = name;

	// パーティクルを読み込む
	particleHandle_ = engine_->LoadParticleEmitter(this);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="particleHandle"></param>
void BillboardParticleEmitter::Initliaze(const MugenEngine* engine, const Camera3D* camera3d, ParticleHandle particleHandle)
{
	// nullptrチェック
	assert(engine);
	assert(camera3d);

	// 引数を受け取る
	engine_ = engine;
	camera3d_ = camera3d;
	particleHandle_ = particleHandle;
}

/// <summary>
/// 更新処理
/// </summary>
void BillboardParticleEmitter::Update()
{
	engine_->UpdateRegistParticle(particleHandle_);
}

/// <summary>
/// 描画処理
/// </summary>
void BillboardParticleEmitter::Draw()
{
	engine_->DrawBillboardParticle(particleHandle_, camera3d_);
}



/// <summary>
/// テクスチャハンドルのSetter
/// </summary>
/// <param name="textureHandle"></param>
void BillboardParticleEmitter::SetTextureHandle(TextureHandle textureHandle)
{
	engine_->SetParticleTextureHandle(particleHandle_, textureHandle);
}