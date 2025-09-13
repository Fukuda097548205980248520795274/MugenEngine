#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../../LogFile/LogFile.h"
#include "../DirectXHeap/DirectXHeap.h"

class DirectXBuffering
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="hwnd"></param>
	/// <param name="kClientWidth"></param>
	/// <param name="kClientHeight"></param>
	void Initialize(LogFile* logFile, DirectXHeap* directXHeap, IDXGIFactory7* dxgiFactory, ID3D12Device* device,
		HWND hwnd, const int32_t* kClientWidth, const int32_t* kClientHeight, ID3D12CommandQueue* commandQueue);

	/// <summary>
	/// スワップチェーンのGetter
	/// </summary>
	/// <returns></returns>
	IDXGISwapChain4* GetSwapChain()const { return swapChain_.Get(); }

	/// <summary>
	/// スワップチェーンのRTV用CPUハンドルのGetter
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetSwapChainRtvCPUHandle(UINT index)const { return rtvCPUHandle_[index]; }

	/// <summary>
	/// スワップチェーンのリソースのGetter
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	ID3D12Resource* GetSwapChainResource(UINT index)const { return swapChainResource_[index].Get(); }


private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// DXGIファクトリー
	IDXGIFactory7* dxgiFactory_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// ウィンドウハンドル
	HWND hwnd_;

	// クライアント領域横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域縦幅
	const int32_t* kClientHeight_ = nullptr;

	// コマンドキュー
	ID3D12CommandQueue* commandQueue_ = nullptr;



	// スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

	// スワップチェーンのリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> swapChainResource_[2] = { nullptr };

	// CPUハンドル
	D3D12_CPU_DESCRIPTOR_HANDLE rtvCPUHandle_[2]{};

	// RTV
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};
};

