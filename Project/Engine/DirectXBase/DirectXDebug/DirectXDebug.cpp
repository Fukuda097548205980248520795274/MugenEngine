#include "DirectXDebug.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
void DirectXDebug::Initialize(LogFile* logFile)
{
	// nullptrチェック
	assert(logFile);

	// 引数を受け取る
	logFile_ = logFile;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController_))))
	{
		// デバッグレイヤーを有効化する
		debugController_->EnableDebugLayer();
		logFile_->Log("Enable DebugLayer \n");

		// GPU側でもチェックを行うようにする
		debugController_->SetEnableGPUBasedValidation(TRUE);
	}
}

/// <summary>
/// 警告・エラーで停止させる
/// </summary>
/// <param name="device"></param>
void DirectXDebug::Stop(ID3D12Device* device)
{
	ID3D12InfoQueue* infoQueue = nullptr;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		// 危険なエラーで停止させる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);

		// エラーで停止させる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

		// 警告で停止させる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		// 解放する
		infoQueue->Release();


		// 抑制するメッセージのID
		D3D12_MESSAGE_ID denyIDs[] = { D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE };

		// 抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };

		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIDs);
		filter.DenyList.pIDList = denyIDs;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;

		// 指定したメッセージの表示を抑制
		infoQueue->PushStorageFilter(&filter);
	}
}


/// <summary>
/// 解放漏れを検知する
/// </summary>
void LeakChecker()
{
	// 解放漏れを検知する
	IDXGIDebug1* debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug))))
	{
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		debug->Release();
	}
}