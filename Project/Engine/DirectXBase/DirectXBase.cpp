#include "DirectXBase.h"


/// <summary>
/// デストラクタ
/// </summary>
DirectXBase::~DirectXBase()
{
#ifdef _DEVELOPMENT
	// ImGuiの終了処理
	imGuiRender_->Finalize();
#endif
}


/// <summary>
/// 初期化
/// </summary>
void DirectXBase::Initialize(LogFile* logFile, const WinApp* winApp, const int32_t* kClientWidth, const int32_t* kClientHeight)
{
	// nullptrチェック
	assert(logFile);
	assert(winApp);
	assert(kClientWidth);
	assert(kClientHeight);

	// 引数を受け取る
	logFile_ = logFile;
	winApp_ = winApp;
	kClientWidth_ = kClientWidth;
	kClientHeight_ = kClientHeight;


	// FPS固定初期化
	InitializeFixFPS();


#ifdef _DEBUG
	// DirectXデバッグの生成と初期化
	directXDebug_ = std::make_unique<DirectXDebug>();
	directXDebug_->Initialize(logFile_);
#endif


	// DirectXデバイスの生成と初期化
	directXDevice_ = std::make_unique<DirectXDevice>();
	directXDevice_->Initialize(logFile_);


#ifdef _DEBUG
	// エラー・警告で停止するようにする
	directXDebug_->Stop(directXDevice_->GetDevice());
#endif


	// DirectXコマンドの生成と初期化
	directXCommand_ = std::make_unique<DirectXCommand>();
	directXCommand_->Initialize(directXDevice_->GetDevice(), logFile_);

	// DirectXヒープの生成と初期化
	directXHeap_ = std::make_unique<DirectXHeap>();
	directXHeap_->Initialize(directXDevice_->GetDevice(), logFile_);

	// DirectXバッファリングの生成と初期化
	directXBuffering_ = std::make_unique<DirectXBuffering>();
	directXBuffering_->Initialize(logFile_, directXHeap_.get(), directXDevice_->GetDXGIfactory(), directXDevice_->GetDevice(),
		winApp_->GetHwnd(), kClientWidth_, kClientHeight_, directXCommand_->GetCommandQueue());

	// DirectXフェンスの生成と初期化
	directXFence_ = std::make_unique<DirectXFence>();
	directXFence_->Initialize(logFile_, directXDevice_->GetDevice());

	// DirectX描画の生成と初期化
	directXDraw_ = std::make_unique<DirectXDraw>();
	directXDraw_->Initialize(logFile_, directXHeap_.get(), directXBuffering_.get(),
		kClientWidth_, kClientHeight_, directXCommand_->GetCommandList(), directXDevice_->GetDevice());

	// 深度情報リソースの生成と初期化
	resourceDepthStencil_ = std::make_unique<ResourcesDepthStencil>();
	resourceDepthStencil_->Initialize(directXHeap_.get(), directXDevice_->GetDevice(), kClientWidth_, kClientHeight_);


#ifdef _DEVELOPMENT
	// ImGui描画システムを初期化する
	imGuiRender_ = std::make_unique<ImGuiRender>();
	imGuiRender_->Initialize(winApp_, directXDevice_.get(), directXCommand_.get(), directXBuffering_.get(), directXHeap_.get());
#endif
}



/// <summary>
/// 描画前処理
/// </summary>
void DirectXBase::PreDraw()
{
#ifdef _DEVELOPMENT
	// フレームの開始をImGuiに伝える
	imGuiRender_->NewFrameStart();
#endif


	// ブレンドモードをリセットする
	directXDraw_->ResetBlendMode();

	// プリミティブカウントを初期化する
	directXDraw_->InitializeDrawNum();

	// 深度情報リソースのハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = resourceDepthStencil_->GetDsvCPUDescriptorHandle();

	// オフスクリーンのクリア設定
	directXDraw_->OffscreenClear(dsvHandle);

	// 描画用のディスクリプタヒープを設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { directXHeap_->GetSrvDescriptorHeap() };
	directXCommand_->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);

#ifdef _DEVELOPMENT
	// Dockスペースを作成する
	imGuiRender_->CreateDockSpace();
#endif 
}

/// <summary>
/// 描画後処理
/// </summary>
void DirectXBase::PostDraw()
{

	// バックバッファのインデックスを取得する
	UINT backBufferIndex = directXBuffering_->GetSwapChain()->GetCurrentBackBufferIndex();

	// バックバッファのリソースを取得する
	ID3D12Resource* backBufferResource = directXBuffering_->GetSwapChainResource(backBufferIndex);

	// バックバッファのCPUハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferCPUHandle = directXBuffering_->GetSwapChainRtvCPUHandle(backBufferIndex);


	// バックバッファリソース Present -> RenderTarget
	TransitionBarrier(backBufferResource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, directXCommand_->GetCommandList());

	// 描画先のRTVを設定する
	directXCommand_->GetCommandList()->OMSetRenderTargets(1, &backBufferCPUHandle, false, nullptr);

	// 指定した色で画面全体をクリアする
	float clearColor[] = { 0.1f , 0.1f , 0.1f , 0.0f };
	directXCommand_->GetCommandList()->ClearRenderTargetView(backBufferCPUHandle, clearColor, 0, nullptr);


	// RTVをスワップチェーンにコピーする
	directXDraw_->DrawRtvToSwapChain();


	// ImGuiDockingに最終的なオフスクリーンを描画する
#ifdef _DEVELOPMENT
	// オフスクリーン最後のリソース
	ID3D12Resource* lastOffscreenResource = directXDraw_->GetLastOffscreenResource();

	// オフスクリーン最後のGPUハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE lastOffscreenDescriptorHandleGPU = directXDraw_->GetLastOffscreenDescriptorHandleGPU();

	// ImGuiに表示するスクリーンを描画する
	imGuiRender_->DrawImGuiScreen(lastOffscreenResource, lastOffscreenDescriptorHandleGPU);
#endif


	// バックバッファリソース RenderTarget -> Present
	TransitionBarrier(backBufferResource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT, directXCommand_->GetCommandList());


	// コマンドの内容を確定させる（閉じる）
	HRESULT hr = directXCommand_->GetCommandList()->Close();
	assert(SUCCEEDED(hr));

	// GPUにコマンドリストの実行を行わせる
	ID3D12CommandList* commandLists[] = { directXCommand_->GetCommandList() };
	directXCommand_->GetCommandQueue()->ExecuteCommandLists(1, commandLists);

	// GPUとOSに画面の交換を行うよう通知する
	directXBuffering_->GetSwapChain()->Present(1, 0);

	// GPUにシグナルを送る
	directXFence_->SnedSignal(directXCommand_->GetCommandQueue());

	// フェンスの値を確認してGPUを待つ
	directXFence_->WaitGPU();

	// FPS固定更新処理
	UpdateFixFPS();

	// 次のフレーム用のコマンドリストを準備
	hr = directXCommand_->GetCommandAllocator()->Reset();
	assert(SUCCEEDED(hr));

	hr = directXCommand_->GetCommandList()->Reset(directXCommand_->GetCommandAllocator(), nullptr);
	assert(SUCCEEDED(hr));
}




/// <summary>
/// FPS固定初期化
/// </summary>
void DirectXBase::InitializeFixFPS()
{
	// 現在時間を初期化する
	reference_ = std::chrono::steady_clock::now();
}

/// <summary>
/// FPS固定更新処理
/// </summary>
void DirectXBase::UpdateFixFPS()
{
	// 1/60 秒ぴったりの時間
	const std::chrono::microseconds kMinTime(uint64_t(1000000.0f / 60.0f));

	// 1/60 秒よりわずかに短い時間
	const std::chrono::microseconds kMinCheckTime(uint64_t(1000000.0f / 65.0f));


	// 現在時間を取得する
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

	// 前回の記録から経過時間を取得する
	std::chrono::microseconds elapsed =
		std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);


	// 1/60 秒、経過していない場合
	if (elapsed < kMinCheckTime)
	{
		// 1/60 秒経過するまで微小なスリープを繰り返す
		while (std::chrono::steady_clock::now() - reference_ < kMinTime)
		{
			// 1マイクロ秒スリープ
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}

	// 現在の時間を記録する
	reference_ = std::chrono::steady_clock::now();
}