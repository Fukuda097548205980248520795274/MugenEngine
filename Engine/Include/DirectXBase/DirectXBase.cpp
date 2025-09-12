#include "DirectXBase.h"

/// <summary>
/// 初期化
/// </summary>
void DirectXBase::Initialize(LogFile* logFile, HWND hwnd, const int32_t* kClientWidth, const int32_t* kClientHeight)
{
	// nullptrチェック
	assert(logFile);
	assert(kClientWidth);
	assert(kClientHeight);

	// 引数を受け取る
	logFile_ = logFile;
	hwnd_ = hwnd;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;


	// DirectXデバイスの生成と初期化
	directXDevice_ = std::make_unique<DirectXDevice>();
	directXDevice_->Initialize(logFile_);

	// DirectXコマンドの生成と初期化
	directXCommand_ = std::make_unique<DirectXCommand>();
	directXCommand_->Initialize(directXDevice_->GetDevice(), logFile_);

	// コマンド関連のオブジェクトを取得する
	commandQueue_ = directXCommand_->GetCommandQueue();
	commandAllocator_ = directXCommand_->GetCommandAllocator();
	commandList_ = directXCommand_->GetCommandList();

	// DirectXヒープの生成と初期化
	directXHeap_ = std::make_unique<DirectXHeap>();
	directXHeap_->Initialize(directXDevice_->GetDevice(), logFile_);

	// DirectXバッファリングの生成と初期化
	directXBuffering_ = std::make_unique<DirectXBuffering>();
	directXBuffering_->Initialize(logFile_, directXHeap_.get(), directXDevice_->GetDXGIfactory(), directXDevice_->GetDevice(),
		hwnd_, kClientWidth_, kClientHeight_, directXCommand_->GetCommandQueue());
}



/// <summary>
/// 描画前処理
/// </summary>
void DirectXBase::PreDraw()
{
	// バックバッファのインデックスを取得する
	UINT backBufferIndex = directXBuffering_->GetSwapChain()->GetCurrentBackBufferIndex();

	// バックバッファのCPUハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferCPUHandle = directXBuffering_->GetSwapChainRtvCPUHandle(backBufferIndex);


	// 描画先のRTVを設定する
	commandList_->OMSetRenderTargets(1, &backBufferCPUHandle, false, nullptr);

	// 指定した色で画面全体をクリアする
	float clearColor[] = { 0.1f , 0.1f , 0.1f , 1.0f };
	commandList_->ClearRenderTargetView(backBufferCPUHandle, clearColor, 0, nullptr);
}

/// <summary>
/// 描画後処理
/// </summary>
void DirectXBase::PostDraw()
{
	// コマンドの内容を確定させる（閉じる）
	HRESULT hr = commandList_->Close();
	assert(SUCCEEDED(hr));

	// GPUにコマンドリストの実行を行わせる
	ID3D12CommandList* commandLists[] = { commandList_ };
	commandQueue_->ExecuteCommandLists(1, commandLists);

	// GPUとOSに画面の交換を行うよう通知する
	directXBuffering_->GetSwapChain()->Present(1, 0);

	// 次のフレーム用のコマンドリストを準備
	hr = commandAllocator_->Reset();
	assert(SUCCEEDED(hr));

	hr = commandList_->Reset(commandAllocator_, nullptr);
	assert(SUCCEEDED(hr));
}