#pragma once
#include <vector>
#include <memory>
#include "../ParticleEmitter/ParticleEmitter.h"
#include "../../DirectXHeap/DirectXHeap.h"

#include "../ResourcesData/ResourcesParticleCube/ResourcesParticleCube.h"

// DirectX描画
class DirectXDraw;

class ParticleStore
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXHeap"></param>
	void Initialize(DirectXDraw* directXDraw, DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// パーティクルを読み込む
	/// </summary>
	/// <param name="particleEmitter"></param>
	/// <returns></returns>
	uint32_t LoadParticle(ParticleEmitter* particleEmitter);

	/// <summary>
	/// パーティクルの放出処理
	/// </summary>
	/// <param name="particleHandle"></param>
	void EmitParticle(uint32_t particleHandle)const { particleData_[particleHandle]->particleEmitter_->Emit(); }

	/// <summary>
	/// パーティクルの更新処理
	/// </summary>
	/// <param name="particleHandle"></param>
	void UpdateParticle(uint32_t particleHandle)const { particleData_[particleHandle]->particleEmitter_->Update(); };

	/// <summary>
	/// パーティクルの描画処理
	/// </summary>
	/// <param name="particleHandle"></param>
	void DrawParticle(uint32_t particleHandle)const;




private:

	// DirectX描画
	DirectXDraw* directXDraw_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// パーティクルデータ
	class ParticleDatum
	{
	public:

		// 名前
		std::string name_;

		// リソース
		std::unique_ptr<ResourcesParticleCube> resources_ = nullptr;

		// ハンドル
		uint32_t handle_ = 0;

		// パーティクルエミッター
		ParticleEmitter* particleEmitter_ = nullptr;
	};

	// パーティクルデータ
	std::vector<std::unique_ptr<ParticleDatum>> particleData_;
};

