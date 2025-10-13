#include "ModelParticleEmitter.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="numMaxParticle"></param>
void ModelParticleEmitter::Initliaze(const Camera3D* camera3d, uint32_t numMaxParticle, ModelHandle modelHandle, const std::string& name)
{
	// nullptrチェック
	assert(camera3d);

	// 引数を受け取る
	camera3d_ = camera3d;
	numMaxParticle_ = numMaxParticle;
	modelHandle_ = modelHandle;
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
void ModelParticleEmitter::Initliaze(const Camera3D* camera3d, ParticleHandle particleHandle)
{
	// 引数を受け取る
	camera3d_ = camera3d;
	particleHandle_ = particleHandle;

	// エンジンのインスタンスを取得する
	engine_ = MugenEngine::GetInstance();
}

/// <summary>
/// 更新処理
/// </summary>
void ModelParticleEmitter::Update()
{
	engine_->UpdateRegistParticle(particleHandle_);
}

/// <summary>
/// 描画処理
/// </summary>
void ModelParticleEmitter::Draw()
{
	engine_->DrawModelParticle(particleHandle_, camera3d_);
}

/// <summary>
/// モデルハンドルのSetter
/// </summary>
/// <param name="modelHandle"></param>
void ModelParticleEmitter::SetModelHandle(ModelHandle modelHandle)
{
	engine_->SetParticleModelHandle(particleHandle_, modelHandle);
}