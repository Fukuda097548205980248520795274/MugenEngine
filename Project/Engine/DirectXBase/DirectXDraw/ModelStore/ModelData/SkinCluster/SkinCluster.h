#pragma once
#include <span>
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>

#include "../Influence/Influence.h"
#include "../SkeletonData/SkeletonData.h"


// スキンクラスター
struct SkinCluster
{
	std::vector<Matrix4x4> inverseBindPoseMatrices;

	Microsoft::WRL::ComPtr<ID3D12Resource> influenceResource;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView;
	std::span<VertexInfluence> mappedInfluence;

	Microsoft::WRL::ComPtr<ID3D12Resource> paletteResource;
	std::span<WellForGPU> mappedPalette;
	std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> paletteSrvHandle;
};


/// <summary>
/// スキンクラスターの更新処理
/// </summary>
/// <param name="skinCluster"></param>
/// <param name="skeleton"></param>
void UpdateSkinCluster(SkinCluster& skinCluster, const Skeleton& skeleton);