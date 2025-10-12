#include "ParticleStore.h"

// インスタンス
ParticleStore* ParticleStore::instance_ = nullptr;

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
ParticleStore* ParticleStore::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new ParticleStore();
	}

	return instance_;
}


/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
/// <param name="directXHeap"></param>
void ParticleStore::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap, ModelStore* modelStore)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(directXHeap);
	assert(modelStore);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	directXHeap_ = directXHeap;
	modelStore_ = modelStore;
}

/// <summary>
/// 終了処理
/// </summary>
void ParticleStore::Finalize()
{
	delete instance_;
}



/// <summary>
/// パーティクルエミッターを読み込む
/// </summary>
ParticleHandle ParticleStore::LoadParticleEmitter(BillboardParticleEmitter* particleEmitter)
{
	// 最大パーティクル数
	uint32_t numMaxParticle = particleEmitter->GetNumMaxParticle();

	// パーティクルハンドルを作成する
	ParticleHandle particleHandle{};
	particleHandle.value = static_cast<uint32_t>(particleData_.size());

	// ビルボード用のパーティクルデータを用意する
	std::unique_ptr<BiilboardParticleData> particleData = std::make_unique<BiilboardParticleData>();
	particleData->Initialize(device_, commandList_, directXHeap_, numMaxParticle, particleHandle, particleEmitter->GetNameP());

	// テクスチャハンドルを取得する
	particleData->textureHandle_ = particleEmitter->GetTextureHandle();


	// リストに登録する
	particleData_.push_back(std::move(particleData));

	return particleHandle;
}

/// <summary>
/// パーティクルエミッターを読み込む
/// </summary>
ParticleHandle ParticleStore::LoadParticleEmitter(ModelParticleEmitter* particleEmitter)
{
	// 最大パーティクル数
	uint32_t numMaxParticle = particleEmitter->GetNumMaxParticle();

	// パーティクルハンドルを作成する
	ParticleHandle particleHandle{};
	particleHandle.value = static_cast<uint32_t>(particleData_.size());

	// モデル用のパーティクルデータを用意する
	std::unique_ptr<ModelParticleData> particleData = std::make_unique<ModelParticleData>();
	particleData->Initialize(device_, commandList_, directXHeap_, numMaxParticle, particleHandle, particleEmitter->GetNameP());

	// モデルハンドルを取得する
	particleData->modelHandle_ = particleEmitter->GetModelHandle();
	particleData->modelResource_ = modelStore_->GetModelInfo(particleData->modelHandle_);


	// リストに登録する
	particleData_.push_back(std::move(particleData));

	return particleHandle;
}


/// <summary>
/// 格納されたパーティクルの更新処理
/// </summary>
void ParticleStore::UpdateRegistParticle(ParticleHandle particleHandle)
{
	// 個々の更新処理
	particleData_[particleHandle.value]->Update();
}
