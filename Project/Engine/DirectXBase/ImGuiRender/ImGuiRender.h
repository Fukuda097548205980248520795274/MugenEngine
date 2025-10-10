#pragma once
#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

#include "WinApp/WinApp.h"
#include "DirectXBase/DirectXDevice/DirectXDevice.h"
#include "DirectXBase/DirectXCommand/DirectXCommand.h"
#include "DirectXBase/DirectXBuffering/DirectXBuffering.h"
#include "DirectXBase/DirectXHeap/DirectXHeap.h"
#include "Func/DirectXTransitionBarrier/DirectXTransitionBarrier.h"

class ImGuiRender
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="winApp"></param>
	/// <param name="directXDevice"></param>
	/// <param name="directXCommand"></param>
	/// <param name="directXBuffering"></param>
	/// <param name="directXHeap"></param>
	void Initialize(const WinApp* winApp, DirectXDevice* directXDevice, DirectXCommand* directXCommand, DirectXBuffering* directXBuffering, DirectXHeap* directXHeap);

	/// <summary>
	/// 新規フレーム開始
	/// </summary>
	void NewFrameStart();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// Dockスペースを作成する
	/// </summary>
	void CreateDockSpace();

	/// <summary>
	/// ImGuiのスクリーンを描画する
	/// </summary>
	/// <param name="lastOffscreenResource"></param>
	/// <param name="lastOffscreenSrvGpuHandle"></param>
	void DrawImGuiScreen(ID3D12Resource* lastOffscreenResource, D3D12_GPU_DESCRIPTOR_HANDLE lastOffscreenSrvGpuHandle);


private:

	
	// ウィンドウアプリケーション
	const WinApp* winApp_ = nullptr;

	// DirectXデバイス
	DirectXDevice* directXDevice_ = nullptr;

	// DirectXコマンド
	DirectXCommand* directXCommand_ = nullptr;

	// DirectXバッファリング
	DirectXBuffering* directXBuffering_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;
};

