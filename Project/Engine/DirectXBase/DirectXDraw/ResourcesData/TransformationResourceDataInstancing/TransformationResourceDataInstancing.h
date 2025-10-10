#pragma once
#include <algorithm>

#include "DirectXBase/DirectXHeap/DirectXHeap.h"
#include "../../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../../DataForGPU/TransformationData/TransformationData.h"

class TransformationResourceDataInstancing
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	/// <param name="numMaxInstance">最大インスタンス数</param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap, uint32_t numMaxInstance);

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	/// <param name="transformationRootParameter"></param>
	void Register(UINT transformationRootParameter);

	// データ
	TransformationDataForGPU* data_ = nullptr;

private:


	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using DescriptorHandle = std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE>;



	// 最大インスタンス数
	uint32_t numMaxInstance_ = 0;

	// リソース
	ComPtr<ID3D12Resource> resource_ = nullptr;

	// ディスクリプタハンドル
	DescriptorHandle srvDescriptorHandle_;
};

