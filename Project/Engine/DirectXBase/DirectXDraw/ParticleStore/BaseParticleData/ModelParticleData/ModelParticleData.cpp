#include "ModelParticleData.h"

/// <summary>
/// 初期化
/// </summary>
void ModelParticleData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap,
	uint32_t numMaxParticle, ParticleHandle particleHandle, std::string* name)
{
	// 基底クラスの初期化
	BaseParticleData::Initialize(device, commandList, directXHeap, numMaxParticle, particleHandle, name);
}