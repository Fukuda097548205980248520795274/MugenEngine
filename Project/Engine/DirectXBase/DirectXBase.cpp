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


	// ImGuiを初期化する
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// ImGuiの初期化後
	ImGuiIO& io = ImGui::GetIO();
	// ドッキング機能を有効にする
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// ✅ Viewport機能の初期化
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		// Win32で追加のウィンドウを作成・管理するための処理をフック
		ImGui_ImplWin32_EnableDpiAwareness();
	}

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp_->GetHwnd());
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
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX12_NewFrame();
	ImGui::NewFrame();


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


#ifdef _DEVELOPMENT
	directXDraw_->ImGuiOffscree();
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




void CreateDockSpace(const char* name)
{
	static bool opt_fullscreen = true;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// パディングを0に（メインDockSpaceの余白をなくす）
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace", nullptr, window_flags);

	ImGui::PopStyleVar(3); // WindowPadding, Rounding, BorderSizeを戻す

	// DockSpace作成（バーなし、背景のみ）
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	ImGui::End();
}