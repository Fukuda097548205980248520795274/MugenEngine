#pragma once
#include "../BaseParticleData.h"

class BiilboardParticleData : public BaseParticleData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap,
		uint32_t numMaxParticle, ParticleHandle particleHandle) override;
};

