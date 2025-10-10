#include "OffscreenDraw.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
/// <param name="directXBuffering"></param>
/// <param name="directXHeap"></param>
void OffscreenDraw::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, 
	LogFile* logFile, DirectXBuffering* directXBuffering, DirectXHeap* directXHeap, DirectXShaderCompile* directXShaderCompile)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(logFile);
	assert(directXBuffering);
	assert(directXHeap);
	assert(directXShaderCompile);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	logFile_ = logFile;
	directXBuffering_ = directXBuffering;
	directXHeap_ = directXHeap;
	directXShaderCompile_ = directXShaderCompile;


	// レンダーテクスチャリソースを生成する
	for (uint32_t i = 0; i < kNumMaxOffscreen; ++i)
	{
		std::unique_ptr<RenderTargetResources> renderTargetResource = std::make_unique<RenderTargetResources>();
		renderTargetResource->Initialize(device_, commandList_, directXBuffering_, directXHeap_);

		renderTargetResources_.push_back(std::move(renderTargetResource));
	}

	// 頂点シェーダのバイナリデータを取得する
	vertexShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Resources/Shader/PostEffect/Fullscreen.VS.hlsl", L"vs_6_0");
	assert(vertexShaderBlob_ != nullptr);


	// CopyImage用のPSOの生成と初期化
	psoCopyImage_ = std::make_unique<PSOCopyImage>();
	psoCopyImage_->Initialize(logFile_, directXShaderCompile_, vertexShaderBlob_.Get(), device_, commandList_);
}

/// <summary>
/// オフスクリーンのクリア設定
/// </summary>
void OffscreenDraw::ClearOffscree(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
{
	renderTargetResources_[numUsesOffscreen_]->Clear(dsvHandle);

	// カウントする
	++numUsesOffscreen_;
}

/// <summary>
/// 使用したオフスクリーン数をリセットする
/// </summary>
void OffscreenDraw::ResetNumOffscreen()
{
	numUsesOffscreen_ = 0;
}



/// <summary>
/// 最終的なオフスクリーンをスワップチェーンにコピーする
/// </summary>
void OffscreenDraw::DrawRtvToSwapChain()
{
	// リソースを取得し、バリアを張る
	ID3D12Resource* resource = renderTargetResources_[numUsesOffscreen_ - 1]->GetResource();
	TransitionBarrier(resource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, commandList_);


	//  PSOの設定
	psoCopyImage_->RegisterPSO();

	// RenderTargetResourcesの設定
	renderTargetResources_[numUsesOffscreen_ - 1]->Register(0);

	// 頂点は3つ
	commandList_->DrawInstanced(3, 1, 0, 0);


	// バリアを張る
	TransitionBarrier(resource, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, commandList_);
}