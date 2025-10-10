#include "ImGuiRender.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="winApp"></param>
/// <param name="directXDevice"></param>
/// <param name="directXBuffering"></param>
/// <param name="directXHeap"></param>
void ImGuiRender::Initialize(const WinApp* winApp, DirectXDevice* directXDevice, DirectXCommand* directXCommand, DirectXBuffering* directXBuffering, DirectXHeap* directXHeap)
{
	// nullptrチェック
	assert(winApp);
	assert(directXDevice);
	assert(directXCommand);
	assert(directXBuffering);
	assert(directXHeap);

	// 引数を受け取る
	winApp_ = winApp;
	directXDevice_ = directXDevice;
	directXCommand_ = directXCommand;
	directXBuffering_ = directXBuffering;
	directXHeap_ = directXHeap;


	// ImGuiを初期化する
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// ImGuiの初期化後
	ImGuiIO& io = ImGui::GetIO();
	// ドッキング機能を有効にする
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Viewport機能の初期化
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
/// 新規フレーム開始
/// </summary>
void ImGuiRender::NewFrameStart()
{
	// フレームの開始をImGuiに伝える
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX12_NewFrame();
	ImGui::NewFrame();
}

/// <summary>
/// 終了処理
/// </summary>
void ImGuiRender::Finalize()
{
	// ImGuiの終了処理
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

/// <summary>
/// Dockスペースを作成する
/// </summary>
void ImGuiRender::CreateDockSpace()
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

/// <summary>
/// ImGuiのスクリーンを描画する
/// </summary>
/// <param name="lastOffscreenResource"></param>
/// <param name="lastOffscreenSrvGpuHandle"></param>
void ImGuiRender::DrawImGuiScreen(ID3D12Resource* lastOffscreenResource, D3D12_GPU_DESCRIPTOR_HANDLE lastOffscreenSrvGpuHandle)
{
	// RenderTarget -> PixelShaderResource
	TransitionBarrier(lastOffscreenResource,
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, directXCommand_->GetCommandList());

	ImGui::Begin("Scene");

	ImTextureID texId = (ImTextureID)(lastOffscreenSrvGpuHandle.ptr);

	ImVec2 availSize = ImGui::GetContentRegionAvail(); // ウィンドウ内の空きサイズ

	float texWidth = static_cast<float>(directXBuffering_->GetSwapChainDesc().Width);
	float texHeight = static_cast<float>(directXBuffering_->GetSwapChainDesc().Height);
	float aspectRatio = texWidth / texHeight;

	// アスペクト比を保ちつつ、ウィンドウサイズ内に最大表示
	ImVec2 imageSize;

	float availAspect = availSize.x / availSize.y;
	if (availAspect > aspectRatio) {
		// 横に余裕あり → 高さに合わせる
		imageSize.y = availSize.y;
		imageSize.x = availSize.y * aspectRatio;
	} else {
		imageSize.x = availSize.x;
		imageSize.y = availSize.x / aspectRatio;
	}

	// 中央寄せ（X方向、Y方向両方）
	ImVec2 cursorPos = ImGui::GetCursorPos();
	ImVec2 newCursorPos = ImVec2(
		cursorPos.x + (availSize.x - imageSize.x) * 0.5f,
		cursorPos.y + (availSize.y - imageSize.y) * 0.5f
	);

	ImGui::SetCursorPos(newCursorPos);

	ImGui::Image(texId, imageSize);

	ImGui::End();


	// ImGuiの内部コマンドを生成する
	ImGui::Render();

	// ImGuiを描画する
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), directXCommand_->GetCommandList());

	// PixelShaderResource -> RenderTarget
	TransitionBarrier(lastOffscreenResource,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET, directXCommand_->GetCommandList());
}