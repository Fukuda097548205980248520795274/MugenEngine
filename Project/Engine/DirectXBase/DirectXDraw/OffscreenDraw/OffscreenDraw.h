#pragma once
#include "../ResourcesData/RenderTargetResources/RenderTargetResources.h"
#include "DirectXBase/DirectXBuffering/DirectXBuffering.h"
#include "DirectXBase/DirectXDraw/DirectXShaderCompile/DirectXShaderCompile.h"
#include "DirectXBase/DirectXHeap/DirectXHeap.h"

#include "Func/DirectXTransitionBarrier/DirectXTransitionBarrier.h"

#include "BasePSOPostEffect/PSOCopyImage/PSOCopyImage.h"

#include "../Externals/ImGui/imgui.h"
#include "../Externals/ImGui/imgui_impl_dx12.h"
#include "../Externals/ImGui/imgui_impl_win32.h"

class OffscreenDraw
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	/// <param name="directXBuffering"></param>
	/// <param name="directXHeap"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList,
		LogFile* logFile, DirectXBuffering* directXBuffering, DirectXHeap* directXHeap, DirectXShaderCompile* directXShaderCompile);

	/// <summary>
	/// オフスクリーンのクリア設定
	/// </summary>
	void ClearOffscree(D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);

	/// <summary>
	/// 使用したオフスクリーン数をリセットする
	/// </summary>
	void ResetNumOffscreen();

	/// <summary>
	/// 最終的なオフスクリーンをスワップチェーンにコピーする
	/// </summary>
	void DrawRtvToSwapChain();

	/// <summary>
	/// ImGuiにオフスクリーンを描画する
	/// </summary>
	void ImGuiOffscreen();

	/// <summary>
	/// 使用した最後のオフスクリーンのGPUディスクリプタハンドルを取得する
	/// </summary>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetLastOffscreenDescriptorHandleGPU()const { return renderTargetResources_[numUsesOffscreen_ - 1]->GetDescriptorHandleGPU(); }


#pragma region 描画処理

#pragma endregion


private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DirectXバッファリグ
	DirectXBuffering* directXBuffering_ = nullptr;

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;

	// シェーダコンパイラ
	DirectXShaderCompile* directXShaderCompile_ = nullptr;


	// 使用したオフスクリーン数
	uint32_t numUsesOffscreen_ = 0;

	// 最大オフスクリーン数
	const uint32_t kNumMaxOffscreen = 16;

	// レンダーテクスチャ
	std::vector<std::unique_ptr<RenderTargetResources>> renderTargetResources_;


	// 頂点シェーダ
	Microsoft::WRL::ComPtr<IDxcBlob> vertexShaderBlob_ = nullptr;


	// CopyImage用のPSO
	std::unique_ptr<PSOCopyImage> psoCopyImage_ = nullptr;
};

