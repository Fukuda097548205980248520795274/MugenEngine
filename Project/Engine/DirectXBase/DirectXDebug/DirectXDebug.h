#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#include "../../LogFile/LogFile.h"

class DirectXDebug
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	void Initialize(LogFile* logFile);

	/// <summary>
	/// 警告・エラーで停止させる
	/// </summary>
	/// <param name="device"></param>
	void Stop(ID3D12Device* device);

	// Microsoft::WRL 省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


private:

	// ログファイル
	LogFile* logFile_ = nullptr;


	// デバッグコントローラ
	ComPtr<ID3D12Debug1> debugController_ = nullptr;
};

