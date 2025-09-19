#include "MugenEngine.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "dxcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib , "xaudio2.lib")

/// <summary>
/// デストラクタ
/// </summary>
MugenEngine::~MugenEngine()
{
	// オーディオ格納場所
	delete audioStore_;

	// 入力
	delete input_;

	// DirectXベース
	delete directXBase_;

	//ウィンドウアプリケーション
	delete winApp_;

	// ログファイル
	delete logFile_;

	// COMの終了処理
	CoUninitialize();

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

/// <summary>
/// 初期化
/// </summary>
void MugenEngine::Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title)
{
	// 出力用のディレクトリを掘る
	std::filesystem::create_directories("./Engine/Output");

	// COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);

	// 例外が発生したときに起動する
	SetUnhandledExceptionFilter(ExportDump);

	// ログファイルの生成と初期化
	logFile_ = new LogFile();
	logFile_->Initialize();

	// ウィンドウアプリケーションの生成と初期化
	winApp_ = new WinApp();
	winApp_->Initialize(clientWidth, clientHeight, title);

	// クライアント領域のポインタを取得する
	kClientWidth_ = winApp_->GetClientWidthP();
	kClientHeight_ = winApp_->GetClientHeightP();

	// DirectXベースの生成と初期化
	directXBase_ = new DirectXBase();
	directXBase_->Initialize(logFile_, winApp_->GetHwnd(), kClientWidth_, kClientHeight_);

	// 入力の生成と初期化
	input_ = new Input();
	input_->Initialize(logFile_, winApp_->GetWndClass(), winApp_->GetHwnd());

	// オーディオ格納場所の生成と初期化
	audioStore_ = new AudioStore();
	audioStore_->Initialize(logFile_);
}

/// <summary>
/// フレーム開始処理
/// </summary>
void MugenEngine::FrameStart()
{
	// 全ての入力情報を取得する
	input_->CheckInputInfo();

	// 流れていない音楽を削除する
	audioStore_->DeletePlayAudio();

	// 描画前処理
	directXBase_->PreDraw();
}

/// <summary>
/// フレーム終了処理
/// </summary>
void MugenEngine::FrameEnd()
{
	// 描画処理
	directXBase_->PostDraw();

	// 全ての入力情報をコピーする
	input_->CopyInputInfo();
}