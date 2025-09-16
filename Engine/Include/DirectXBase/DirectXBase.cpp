#include "DirectXBase.h"


/// <summary>
/// デストラクタ
/// </summary>
DirectXBase::~DirectXBase()
{
	// ImGuiの終了処理
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}


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
		hwnd_, kClientWidth_, kClientHeight_, directXCommand_->GetCommandQueue());

	// DirectXフェンスの生成と初期化
	directXFence_ = std::make_unique<DirectXFence>();
	directXFence_->Initialize(logFile_, directXDevice_->GetDevice());

	// DirectX描画の生成と初期化
	directXDraw_ = std::make_unique<DirectXDraw>();
	directXDraw_->Initialize(logFile_,directXHeap_.get(), kClientWidth_, kClientHeight_, directXCommand_->GetCommandList(), directXDevice_->GetDevice());

	// 深度情報リソースの生成と初期化
	resourceDepthStencil_ = std::make_unique<ResourcesDepthStencil>();
	resourceDepthStencil_->Initialize(directXHeap_.get(), directXDevice_->GetDevice(), kClientWidth_, kClientHeight_);


	// ImGuiを初期化する
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd_);
	ImGui_ImplDX12_Init(directXDevice_->GetDevice(), directXBuffering_->GetSwapChainDesc().BufferCount,
		directXBuffering_->GetRtvDesc().Format, directXHeap_->GetSrvDescriptorHeap(),
		directXHeap_->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), directXHeap_->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
}



/// <summary>
/// 描画前処理
/// </summary>
void DirectXBase::PreDraw()
{
	// フレームの開始をImGuiに伝える
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	// バックバッファのインデックスを取得する
	UINT backBufferIndex = directXBuffering_->GetSwapChain()->GetCurrentBackBufferIndex();

	// バックバッファのCPUハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferCPUHandle = directXBuffering_->GetSwapChainRtvCPUHandle(backBufferIndex);

	// バックバッファのリソースを取得する
	ID3D12Resource* backBufferResource = directXBuffering_->GetSwapChainResource(backBufferIndex);


	// バックバッファリソース Present -> RenderTarget
	TransitionBarrier(backBufferResource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET, directXCommand_->GetCommandList());

	// 深度情報リソースのハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = resourceDepthStencil_->GetDsvCPUDescriptorHandle();

	// 描画先のRTVとDSVを設定する
	directXCommand_->GetCommandList()->OMSetRenderTargets(1, &backBufferCPUHandle, false, &dsvHandle);

	// 指定した色で画面全体をクリアする
	float clearColor[] = { 0.1f , 0.1f , 0.1f , 1.0f };
	directXCommand_->GetCommandList()->ClearRenderTargetView(backBufferCPUHandle, clearColor, 0, nullptr);

	// 指定した深度で画面全体をクリアする
	directXCommand_->GetCommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);


	// 描画用のディスクリプタヒープを設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { directXHeap_->GetSrvDescriptorHeap() };
	directXCommand_->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
}

/// <summary>
/// 描画後処理
/// </summary>
void DirectXBase::PostDraw()
{
	// ImGuiの内部コマンドを生成する
	ImGui::Render();

	// ImGuiを描画する
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), directXCommand_->GetCommandList());



	// バックバッファのインデックスを取得する
	UINT backBufferIndex = directXBuffering_->GetSwapChain()->GetCurrentBackBufferIndex();

	// バックバッファのリソースを取得する
	ID3D12Resource* backBufferResource = directXBuffering_->GetSwapChainResource(backBufferIndex);

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

	// 次のフレーム用のコマンドリストを準備
	hr = directXCommand_->GetCommandAllocator()->Reset();
	assert(SUCCEEDED(hr));

	hr = directXCommand_->GetCommandList()->Reset(directXCommand_->GetCommandAllocator(), nullptr);
	assert(SUCCEEDED(hr));
}