#include "ModelParticleEmitter.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="numMaxParticle"></param>
void ModelParticleEmitter::Initliaze(const MugenEngine* engine, uint32_t numMaxParticle, ModelHandle modelHandle, const std::string& name)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
	numMaxParticle_ = numMaxParticle;
	modelHandle_ = modelHandle;
	name_ = name;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="particleHandle"></param>
void ModelParticleEmitter::Initliaze(const MugenEngine* engine, ParticleHandle particleHandle)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
	particleHandle_ = particleHandle;
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

}