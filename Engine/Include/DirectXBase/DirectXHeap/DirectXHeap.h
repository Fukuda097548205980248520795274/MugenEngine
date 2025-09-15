#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../../LogFile/LogFile.h"

class DirectXHeap
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device, LogFile* logFile);

	/// <summary>
	/// SRV用ディスクリプタヒープのGetter
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap* GetSrvDescriptorHeap()const { return srvDescriptorHeap_.Get(); }


	/// <summary>
	/// RTV用のCPUハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetRtvCPUDescriptorHandle();


	/// <summary>
	/// SRV用のCPUハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetSrvCPUDescriptorHandle();

	/// <summary>
	/// SRV用のGPUハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetSrvGPUDescriptorHandle();


	/// <summary>
	/// DSV用のCPUハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetDsvCPUDescriptorHandle();

	/// <summary>
	/// DSV用のGPUハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetDsvGPUDescriptorHandle();


private:

	/// <summary>
	/// ディスクリプタヒープを生成する
	/// </summary>
	/// <returns></returns>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT descriptorNum, bool shaderVisible);

	// デバイス
	ID3D12Device* device_ = nullptr;

	// ログファイル
	LogFile* logFile_ = nullptr;


	// RTV用ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;

	// RTV用ディスクリプタ数
	UINT rtvDescriptorNum_ = 2;

	// RTV用CPUディスクリプタ使用数
	int32_t useRtvCPUDescriptor_ = 0;



	// SRV用ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap_ = nullptr;

	// SRV用ディスクリプタ数
	UINT srvDescriptorNum_ = 128;

	// SRV用CPUディスクリプタ使用数
	int32_t useSrvCPUDescriptor_ = 1;

	// SRV用GPUディスクリプタ使用数
	int32_t useSrvGPUDescriptor_ = 1;



	// DSV用ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;

	// DSV用ディスクリプタ数
	UINT dsvDescriptorNum_ = 1;

	// DSV用CPUディスクリプタ使用数
	int32_t useDsvCPUDescriptor_ = 0;

	// DSV用GPUディスクリプタ使用数
	int32_t useDsvGPUDescriptor_ = 0;
};

