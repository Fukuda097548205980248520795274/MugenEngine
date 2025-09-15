#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxcapi.h>
#include <cassert>
#include <wrl.h>

#include "../../../LogFile/LogFile.h"


class BasePSO
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="vertexShaderBlob"></param>
	/// <param name="pixelShaderBlob"></param>
	/// <param name="device"></param>
	virtual void Initialize(LogFile* logFile, IDxcBlob* vertexShaderBlob, IDxcBlob* pixelShaderBlob, 
		ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// PSOをコマンドリストのセットする
	/// </summary>
	void SetPSOState();


protected:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// 頂点シェーダのバイナリデータ
	IDxcBlob* vertexShaderBlob_ = nullptr;

	// ピクセルシェーダのバイナリデータ
	IDxcBlob* pixelShaderBlob_ = nullptr;

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;



	// シグネチャのバイナリデータ
	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob_ = nullptr;

	// エラーのバイナリデータ
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob_ = nullptr;

	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_ = nullptr;

	// PSO
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_ = nullptr;
};

