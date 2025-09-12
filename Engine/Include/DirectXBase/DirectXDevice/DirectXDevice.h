#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../../LogFile/LogFile.h"
#include "../../Func/ConvertString/ConvertString.h"

class DirectXDevice
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logfile"></param>
	void Initialize(LogFile* logFile);


private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;

	// アダプタ
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter_ = nullptr;

	// デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device_ = nullptr;
};

