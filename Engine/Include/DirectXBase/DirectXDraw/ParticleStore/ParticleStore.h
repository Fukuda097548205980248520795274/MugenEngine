#pragma once
#include <vector>
#include "../ParticleEmitter/ParticleEmitter.h"
#include "../../DirectXHeap/DirectXHeap.h"

class ParticleStore
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXHeap"></param>
	void Initialize(DirectXHeap* directXHeap);

	/// <summary>
	/// パーティクルを読み込む
	/// </summary>
	/// <param name="particleEmitter"></param>
	/// <returns></returns>
	uint32_t LoadParticle(ParticleEmitter* particleEmitter);

	/// <summary>
	/// パーティクルエミッターを取得する
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <returns></returns>
	ParticleEmitter* GetParticleEmitter(uint32_t particleHandle)const { return particleData_[particleHandle]->particleEmitter_; }


private:

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;


	// パーティクルデータ
	class ParticleDatum
	{
	public:

		// 名前
		std::string name_;

		// CPUハンドル
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_{};

		// GPUハンドル
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_{};

		// ハンドル
		uint32_t handle_ = 0;

		// パーティクルエミッター
		ParticleEmitter* particleEmitter_ = nullptr;
	};

	// パーティクルデータ
	std::vector<std::unique_ptr<ParticleDatum>> particleData_;
};

