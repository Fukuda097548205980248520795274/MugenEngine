#include "DirectXHeap.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
void DirectXHeap::Initialize(ID3D12Device* device, LogFile* logFile)
{
	// nullptrチェック
	assert(device);
	assert(logFile);

	// 引数を受け取る
	device_ = device;
	logFile_ = logFile;


	// RTVディスクリプタヒープの生成
	rtvDescriptorHeap_ = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, rtvDescriptorNum_, false);
	logFile_->Log("SUCCEEDED : RtvDescriptorHeap \n");

	// SRVディスクリプタヒープの生成
	srvDescriptorHeap_ = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, srvDescriptorNum_, true);
	logFile_->Log("SUCCEEDED : SrvDescriptorHeap \n");

	// DSVディスクリプタヒープの生成
	dsvDescriptorHeap_ = CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, dsvDescriptorNum_, false);
	logFile_->Log("SUCCEEDED : DsvDescriptorHeap \n");
}

/// <summary>
/// RTV用のCPUハンドルを取得する
/// </summary>
/// <returns></returns>
D3D12_CPU_DESCRIPTOR_HANDLE DirectXHeap::GetRtvCPUDescriptorHandle()
{
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = rtvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	cpuHandle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * useRtvCPUDescriptor_;

	// ログを出力する
	logFile_->Log("\n");
	logFile_->Log("View : RTV \n");
	logFile_->Log("Handle : CPU \n");
	logFile_->Log(std::format("Num : {} \n", useRtvCPUDescriptor_));
	logFile_->Log(std::format("Ptr : {} \n", cpuHandle.ptr));
	logFile_->Log("\n");

	// 数をカウントする
	useRtvCPUDescriptor_++;

	return cpuHandle;
}

/// <summary>
/// SRV用のCPUハンドルを取得する
/// </summary>
/// <returns></returns>
D3D12_CPU_DESCRIPTOR_HANDLE DirectXHeap::GetSrvCPUDescriptorHandle()
{
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = srvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	cpuHandle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * useSrvCPUDescriptor_;

	// ログを出力する
	logFile_->Log("\n");
	logFile_->Log("View : SRV \n");
	logFile_->Log("Handle : CPU \n");
	logFile_->Log(std::format("Num : {} \n", useSrvCPUDescriptor_));
	logFile_->Log(std::format("Ptr : {} \n", cpuHandle.ptr));
	logFile_->Log("\n");

	// 数をカウントする
	useSrvCPUDescriptor_++;

	return cpuHandle;
}

/// <summary>
/// SRV用のGPUハンドルを取得する
/// </summary>
/// <returns></returns>
D3D12_GPU_DESCRIPTOR_HANDLE DirectXHeap::GetSrvGPUDescriptorHandle()
{
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = srvDescriptorHeap_->GetGPUDescriptorHandleForHeapStart();
	gpuHandle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) * useSrvGPUDescriptor_;

	// ログを出力する
	logFile_->Log("\n");
	logFile_->Log("View : SRV \n");
	logFile_->Log("Handle : GPU \n");
	logFile_->Log(std::format("Num : {} \n", useSrvGPUDescriptor_));
	logFile_->Log(std::format("Ptr : {} \n", gpuHandle.ptr));
	logFile_->Log("\n");

	// 数をカウントする
	useSrvGPUDescriptor_++;

	return gpuHandle;
}


/// <summary>
/// DSV用のCPUハンドルを取得する
/// </summary>
/// <returns></returns>
D3D12_CPU_DESCRIPTOR_HANDLE DirectXHeap::GetDsvCPUDescriptorHandle()
{
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = dsvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	cpuHandle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV) * useDsvCPUDescriptor_;

	// ログを出力する
	logFile_->Log("\n");
	logFile_->Log("View : DSV \n");
	logFile_->Log("Handle : CPU \n");
	logFile_->Log(std::format("Num : {} \n", useDsvCPUDescriptor_));
	logFile_->Log(std::format("Ptr : {} \n", cpuHandle.ptr));
	logFile_->Log("\n");

	// 数をカウントする
	useDsvCPUDescriptor_++;

	return cpuHandle;
}

/// <summary>
/// DSV用のGPUハンドルを取得する
/// </summary>
/// <returns></returns>
D3D12_GPU_DESCRIPTOR_HANDLE DirectXHeap::GetDsvGPUDescriptorHandle()
{
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = dsvDescriptorHeap_->GetGPUDescriptorHandleForHeapStart();
	gpuHandle.ptr += device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV) * useDsvGPUDescriptor_;

	// ログを出力する
	logFile_->Log("\n");
	logFile_->Log("View : DSV \n");
	logFile_->Log("Handle : GPU \n");
	logFile_->Log(std::format("Num : {} \n", useDsvGPUDescriptor_));
	logFile_->Log(std::format("Ptr : {} \n", gpuHandle.ptr));
	logFile_->Log("\n");

	// 数をカウントする
	useDsvGPUDescriptor_++;

	return gpuHandle;
}


/// <summary>
/// ディスクリプタヒープを生成する
/// </summary>
/// <returns></returns>
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DirectXHeap::CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType , UINT descriptorNum, bool shaderVisible)
{
	// ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap = nullptr;

	// ディスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType; // ヒープの種類
	descriptorHeapDesc.NumDescriptors = descriptorNum; // ディスクリプタの数
	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	// 生成
	HRESULT hr = device_->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
	assert(SUCCEEDED(hr));

	return descriptorHeap;
}