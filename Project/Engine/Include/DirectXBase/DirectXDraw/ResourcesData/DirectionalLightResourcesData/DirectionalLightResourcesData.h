#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/LightData/LightData.h"
#include "../../../DirectXHeap/DirectXHeap.h"

class DirectionalLightResourcesData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t numLight);

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	/// <param name="rootParameterIndex"></param>
	void Register(UINT lightRootParameterIndex, UINT numLightRootParameterIndex);


	// ライトデータ
	DirectionalLightForGPU* lightData_ = nullptr;

	// ライト数データ
	uint32_t* numLightData_ = nullptr;


private:

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// ライトの最大数
	uint32_t numLight_ = 0;


	// ライトリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> lightResource_ = nullptr;

	// CPUハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE lightCPUHandle_{};

	// GPUハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE lightGPUHandle_{};


	// ライト数リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> numLightResource_ = nullptr;
};

