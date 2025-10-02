#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../../LogFile/LogFile.h"

class DirectXCommand
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device, LogFile* logFile);

	/// <summary>
	/// コマンドキューのGetter
	/// </summary>
	/// <returns></returns>
	ID3D12CommandQueue* GetCommandQueue()const { return commandQueue_.Get(); }

	/// <summary>
	/// コマンドアロケータのGetter
	/// </summary>
	/// <returns></returns>
	ID3D12CommandAllocator* GetCommandAllocator()const { return commandAllocator_.Get(); }

	/// <summary>
	/// コマンドリストのGetter
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList_.Get(); }

	// Microsoft::WRL 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// ログファイル
	LogFile* logFile_ = nullptr;


	// コマンドキュー
	ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;

	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;

	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;
};

