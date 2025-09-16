#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../DirectXShaderCompile/DirectXShaderCompile.h"

class BaseOrganizePSO
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="directXCompile"></param>
	virtual void Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile,
		ID3D12GraphicsCommandList* commandList, ID3D12Device* device);

	/// <summary>
	/// PSOの設定をコマンドリストの登録する
	/// </summary>
	virtual void SetPSOState() = 0;


protected:


	// ログファイル
	LogFile* logFile_ = nullptr;

	// DirectXシェーダコンパイラ
	DirectXShaderCompile* directXShaderCompile_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;


	// 頂点シェーダのバイナリデータ
	Microsoft::WRL::ComPtr<IDxcBlob> vertexShaderBlob_ = nullptr;

	// ピクセルシェーダのバイナリデータ
	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderBlob_ = nullptr;
};

