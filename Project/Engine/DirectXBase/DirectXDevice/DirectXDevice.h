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

	/// <summary>
	/// デバイスのGetter
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDevice()const { return device_.Get(); }

	/// <summary>
	/// DXGIファクトリーのGetter
	/// </summary>
	/// <returns></returns>
	IDXGIFactory7* GetDXGIfactory()const { return dxgiFactory_.Get(); }

	// Microsoft::WRL 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DXGIファクトリー
	ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;

	// アダプタ
	ComPtr<IDXGIAdapter4> useAdapter_ = nullptr;

	// デバイス
	ComPtr<ID3D12Device> device_ = nullptr;
};

