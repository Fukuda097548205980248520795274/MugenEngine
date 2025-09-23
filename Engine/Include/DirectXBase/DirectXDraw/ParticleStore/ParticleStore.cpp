#include "ParticleStore.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="directXHeap"></param>
void ParticleStore::Initialize(DirectXHeap* directXHeap)
{
	// nullptrチェック
	assert(directXHeap);

	// 引数を受け取る
	directXHeap_ = directXHeap;
}

/// <summary>
/// パーティクルを読み込む
/// </summary>
/// <param name="particleEmitter"></param>
/// <returns></returns>
uint32_t ParticleStore::LoadParticle(ParticleEmitter* particleEmitter)
{
	// nullptrチェック
	assert(particleEmitter);

	// 同一のデータがないかを確認する
	for (std::unique_ptr<ParticleDatum>& data : particleData_)
	{
		if (strcmp(particleEmitter->GetName().c_str(), data->name_.c_str()) == 0)
			return data->handle_;
	}

	// 単体パーティクルデータを生成する
	std::unique_ptr<ParticleDatum> particleDatum = std::make_unique<ParticleDatum>();
	particleDatum->particleEmitter_ = particleEmitter;
	particleDatum->cpuHandle_ = directXHeap_->GetSrvCPUDescriptorHandle();
	particleDatum->gpuHandle_ = directXHeap_->GetSrvGPUDescriptorHandle();
	uint32_t handle = static_cast<uint32_t>(particleData_.size());
	particleDatum->handle_ = handle;

	// リストに登録する
	particleData_.push_back(std::move(particleDatum));

	return handle;
}