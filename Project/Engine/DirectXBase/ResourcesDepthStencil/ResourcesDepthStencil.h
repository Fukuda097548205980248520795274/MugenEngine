#pragma once
#include "../../Func/LoadTexture/LoadTexture.h"
#include "../DirectXHeap/DirectXHeap.h"

class ResourcesDepthStencil
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXHeap"></param>
	void Initialize(DirectXHeap* directXHeap, ID3D12Device* device, const int32_t* kClientWidth, const int32_t* kClientHeight);

	/// <summary>
	/// CPUディスクリプタハンドルのGetter
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetDsvCPUDescriptorHandle()const { return cpuHandle_; }

	// Microsoft::WRL 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


private:

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// クライアント領域の横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域の縦幅
	const int32_t* kClientHeight_ = nullptr;



	// 振動情報リソース
	ComPtr<ID3D12Resource> depthStencilResource_ = nullptr;

	// CPUハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle_{};
};

