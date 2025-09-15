#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "DirectXShaderCompile/DirectXShaderCompile.h"

#include "PSOPrimitive/PSOPrimitive.h"

#include "ResourcesTriangle/ResourcesTriangle.h"

#include "Transform/Transform.h"

class DirectXDraw
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="commandList"></param>
	/// <param name="device"></param>
	void Initialize(LogFile* logFile,const int32_t* kClientWidth, const int32_t* kClientHeight,
		ID3D12GraphicsCommandList* commandList, ID3D12Device* device);

	/// <summary>
	/// 三角形を描画する
	/// </summary>
	void DrawTriangle();


private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// クライアント領域の横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域の縦幅
	const int32_t* kClientHeight_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;




	// DirectXシェーダコンパイラ
	std::unique_ptr<DirectXShaderCompile> directXShaderCompiler_ = nullptr;

	// プリミティブ用PSO
	std::unique_ptr<PSOPrimitive> primitivePSO_ = nullptr;


	// ビューポート
	D3D12_VIEWPORT viewport_{};

	// シザー
	D3D12_RECT scissorRect_{};


	// 三角形用のリソース
	std::unique_ptr<ResourcesTriangle> resourcesTriangle_ = nullptr;


	// 図形
	Transform3D transform_;

	// カメラ
	Transform3D camera_;
};

