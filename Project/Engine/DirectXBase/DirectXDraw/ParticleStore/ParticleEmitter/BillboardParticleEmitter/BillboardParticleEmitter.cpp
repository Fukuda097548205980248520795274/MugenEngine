#include "BillboardParticleEmitter.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="numMaxParticle"></param>
void BillboardParticleEmitter::Initliaze(const Camera3D* camera3d, uint32_t numMaxParticle,TextureHandle textureHandle, const std::string& name)
{
	// nullptrチェック
	assert(camera3d);

	// 引数を受け取る
	camera3d_ = camera3d;
	numMaxParticle_ = numMaxParticle;
	textureHandle_ = textureHandle;
	name_ = name;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// パーティクルを読み込む
	particleHandle_ = engine_->LoadParticleEmitter(this);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="particleHandle"></param>
void BillboardParticleEmitter::Initliaze(const Camera3D* camera3d, ParticleHandle particleHandle)
{
	// nullptrチェック
	assert(camera3d);

	// 引数を受け取る
	camera3d_ = camera3d;
	particleHandle_ = particleHandle;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
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


/// <summary>
/// 位置のSetter
/// </summary>
/// <param name="position"></param>
void BillboardParticleEmitter::SetPosition(const Vector3& position)
{
	engine_->SetEmitterPosition(position, particleHandle_);
}