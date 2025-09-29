#pragma once
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/LightData/LightData.h"
#include "../../../DirectXHeap/DirectXHeap.h"

class SpotLightResourcesData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXHeap"></param>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	/// <param name="numLight"></param>
	void Initialize(DirectXHeap* directXHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t numLight);

	/// <summary>
	/// 登録する
	/// </summary>
	/// <param name="lightRootParameterIndex"></param>
	/// <param name="numLightRootParameterIndex"></param>
	void Register(UINT lightRootParameterIndex, UINT numLightRootParameterIndex);


	// ライトデータ
	SpotLightForGPU* lightData_ = nullptr;

	// ライト数データ
	uint32_t* numLightData_ = nullptr;

private:


	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// ライトの数
	uint32_t numLight_ = 0;


	// ライトリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> lightResource_ = nullptr;

	// CPUハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_{};

	// GPUハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_{};


	// ライト数リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> numLightResource_ = nullptr;
};

