#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../DirectXShaderCompile/DirectXShaderCompile.h"
#include "EnumBlendMode/EnumBlendMode.h"

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

	/// <summary>
	/// ブレンドモードのSetter
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendMode(BlendMode blendMode) { blendMode_ = static_cast<int>(blendMode); }

	/// <summary>
	/// ブレンドモードをリセットする
	/// </summary>
	virtual void ResetBlendMode() = 0;

	// Microsoft::WRL の省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

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
	ComPtr<IDxcBlob> vertexShaderBlob_ = nullptr;

	// ピクセルシェーダのバイナリデータ
	ComPtr<IDxcBlob> pixelShaderBlob_ = nullptr;

	// 現在のブレンドモード
	int blendMode_ = static_cast<int>(BlendMode::kNone);
};

