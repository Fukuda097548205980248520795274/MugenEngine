#include "BiilboardParticleData.h"

/// <summary>
/// 初期化
/// </summary>
void BiilboardParticleData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap,
	uint32_t numMaxParticle, ParticleHandle particleHandle)
{
	// 基底クラスの初期化
	BaseParticleData::Initialize(device, commandList, directXHeap, numMaxParticle, particleHandle);
}