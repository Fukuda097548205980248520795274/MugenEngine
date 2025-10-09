#pragma once
#include "Func/LoadTexture/LoadTexture.h"
#include "DirectXBase/DirectXBuffering/DirectXBuffering.h"
#include "DirectXBase/DirectXHeap/DirectXHeap.h"
#include "Func/DirectXTransitionBarrier/DirectXTransitionBarrier.h"

class RenderTargetResources
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="directXBuffering"></param>
	/// <param name="directXHeap"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXBuffering* directXBuffering, DirectXHeap* directXHeap);

	/// <summary>
	/// クリア処理
	/// </summary>
	void Clear(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	void Register(UINT textureRootParameterIndex);

	/// <summary>
	/// リソースのGetter
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetResource()const { return resource_.Get(); }


private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// DirectXバッファリング
	DirectXBuffering* directXBuffering_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;


	// リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> resource_ = nullptr;

	// 最適値カラー
	Vector4 clearColor_ = {};

	// RTVのディスクリプタハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptorHandle_{};

	// SRVのディスクリプタハンドル
	std::pair<D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE> srvDescriptorHandle_{};
};

