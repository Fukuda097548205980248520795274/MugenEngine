#include "ParticleStore.h"
#include "../DirectXDraw.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="directXHeap"></param>
void ParticleStore::Initialize(DirectXDraw* directXDraw, DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(directXDraw);
	assert(directXHeap);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	directXDraw_ = directXDraw;
	directXHeap_ = directXHeap;
	device_ = device;
	commandList_ = commandList;
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
	uint32_t handle = static_cast<uint32_t>(particleData_.size());
	particleDatum->handle_ = handle;

	// リソースを生成する
	particleDatum->resources_ = std::make_unique<ResourcesParticleCube>();
	particleDatum->resources_->Initialize(directXHeap_, device_, commandList_, particleDatum->particleEmitter_->GetNumParticle());

	// リストに登録する
	particleData_.push_back(std::move(particleDatum));

	return handle;
}

/// <summary>
/// パーティクルの描画処理
/// </summary>
/// <param name="particleHandle"></param>
void ParticleStore::DrawParticle(uint32_t particleHandle)const
{
	directXDraw_->DrawParticleCube(particleData_[particleHandle]->particleEmitter_->GetParticles(), particleData_[particleHandle]->resources_.get(),
		particleData_[particleHandle]->particleEmitter_->GetCamera3D(), particleData_[particleHandle]->particleEmitter_->GetTextureHandle());
}