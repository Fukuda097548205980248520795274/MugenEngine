#pragma once
#include "DirectXBase/DirectXHeap/DirectXHeap.h"
#include "BaseParticleData/BiilboardParticleData/BiilboardParticleData.h"
#include "BaseParticleData/ModelParticleData/ModelParticleData.h"
#include "../ModelStore/ModelStore.h"

#include "ParticleEmitter/BillboardParticleEmitter/BillboardParticleEmitter.h"
#include "ParticleEmitter/ModelParticleEmitter/ModelParticleEmitter.h"

class ParticleStore
{
public:

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static ParticleStore* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	/// <param name="directXHeap"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap, ModelStore* modelStore);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();


	/// <summary>
	/// パーティクルエミッターを読み込む
	/// </summary>
	ParticleHandle LoadParticleEmitter(BillboardParticleEmitter* particleEmitter);

	/// <summary>
	/// パーティクルエミッターを読み込む
	/// </summary>
	ParticleHandle LoadParticleEmitter(ModelParticleEmitter* particleEmitter);

	/// <summary>
	/// パーティクルデータのGetter
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <returns></returns>
	BaseParticleData* GetParticleData(ParticleHandle particleHandle)const { return particleData_[particleHandle.value].get(); }

	/// <summary>
	/// モデルハンドルのSetter
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <param name="modelHandle"></param>
	void SetModelHandle(ParticleHandle particleHandle, ModelHandle modelHandle) { particleData_[particleHandle.value]->modelHandle_ = modelHandle; }

	/// <summary>
	/// テクスチャハンドルのSetter
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <param name="textureHandle"></param>
	void SetTextureHandle(ParticleHandle particleHandle, TextureHandle textureHandle) { particleData_[particleHandle.value]->textureHandle_ = textureHandle; }


	/// <summary>
	/// 格納されたパーティクルの更新処理
	/// </summary>
	void UpdateRegistParticle(ParticleHandle particleHandle);


private:

	// シングルトン
	ParticleStore() = default;
	~ParticleStore() = default;
	ParticleStore(ParticleStore&) = delete;
	ParticleStore& operator=(ParticleStore&) = delete;



	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// モデル格納場所
	ModelStore* modelStore_ = nullptr;


	// インスタンス
	static ParticleStore* instance_;

	// パーティクルデータ
	std::vector<std::unique_ptr<BaseParticleData>> particleData_;
};

