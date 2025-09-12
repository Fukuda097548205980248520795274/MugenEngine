#include "DirectXBuffering.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="hwnd"></param>
/// <param name="kClientWidth"></param>
/// <param name="kClientHeight"></param>
void DirectXBuffering::Initialize(LogFile* logFile, DirectXHeap* directXHeap, IDXGIFactory7* dxgiFactory, ID3D12Device* device,
	HWND hwnd, const int32_t* kClientWidth, const int32_t* kClientHeight, ID3D12CommandQueue* commandQueue)
{
	// nullptrチェック
	assert(logFile);
	assert(directXHeap);
	assert(dxgiFactory);
	assert(device);
	assert(kClientWidth);
	assert(kClientHeight);
	assert(commandQueue);

	// 引数を受け取る
	logFile_ = logFile;
	directXHeap_ = directXHeap;
	dxgiFactory_ = dxgiFactory;
	device_ = device;
	hwnd_ = hwnd;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;
	commandQueue_ = commandQueue;


	/*-----------------------------
	    スワップチェーンを生成する
	-----------------------------*/

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	// クライアント領域
	swapChainDesc.Width = *kClientWidth_;
	swapChainDesc.Height = *kClientHeight_;

	// 色の形式
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// マルチサンプルしない
	swapChainDesc.SampleDesc.Count = 1;

	// 描画のターゲットとして利用する
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// ダブルバッファ
	swapChainDesc.BufferCount = 2;

	// モニタに移したら中身を破棄
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;


	// 生成する
	HRESULT hr = dxgiFactory_->CreateSwapChainForHwnd(commandQueue_, hwnd_, 
		&swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChain_.GetAddressOf()));
	assert(SUCCEEDED(hr));

	// スワップチェーン生成成功のログ
	logFile_->Log("SUCCEEDED : SwapChain \n");



	/*------------------------------------
	    スワップチェーンのリソースを取得する
	------------------------------------*/

	// 1つめ
	hr = swapChain_->GetBuffer(0, IID_PPV_ARGS(&swapChainResource_[0]));
	assert(SUCCEEDED(hr));
	logFile_->Log("Get : SwapChainResource 0 \n");

	// 2つめ
	hr = swapChain_->GetBuffer(1, IID_PPV_ARGS(&swapChainResource_[1]));
	assert(SUCCEEDED(hr));
	logFile_->Log("Get : SwapChainResource 1 \n");



	/*-------------------
	    RTVを作成する
	-------------------*/

	// 出力結果をSRGBに変換して書き込む
	rtvDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	// 2Dテクスチャとして書き込む
	rtvDesc_.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	
	// 1つめのリソースにRTVを設定する
	rtvCPUHandle_[0] = directXHeap_->GetRtvCPUDescriptorHandle();
	device_->CreateRenderTargetView(swapChainResource_[0].Get(), &rtvDesc_, rtvCPUHandle_[0]);

	// 2つめのリソースにRTVを設定する
	rtvCPUHandle_[1] = directXHeap_->GetRtvCPUDescriptorHandle();
	device_->CreateRenderTargetView(swapChainResource_[1].Get(), &rtvDesc_, rtvCPUHandle_[1]);
}