#include "WinApp.h"
#include "../../../Externals/ImGui/imgui.h"
#include "../../../Externals/ImGui/imgui_impl_dx12.h"
#include "../../../Externals/ImGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ウィンドウプロシージャ
LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ImGuiを操作すると途中で打ち切ることができる
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)){
		return true;
	}

	// メッセージに応じて固有の処理を行う
	switch (msg)
	{
	case WM_DESTROY:
		// ウィンドウが破棄された

		// OSに対してアプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	// 標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}



/// <summary>
/// デストラクタ
/// </summary>
WinApp::~WinApp()
{
	// ウィンドウハンドルを閉じる
	CloseWindow(hwnd_);
}


/// <summary>
/// 初期化
/// </summary>
void WinApp::Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title)
{
	// 引数を受け取る
	clientWidth_ = clientWidth;
	clientHeight_ = clientHeight;
	title_ = ConvertString(title);


	/*---------------------------
	    ウィンドウクラスを登録する
	---------------------------*/

	// ウィンドウプロシージャ
	wc_.lpfnWndProc = WindowProc;

	// ウィンドウクラス名
	wc_.lpszClassName = L"Mugen";

	// インスタンスハンドル
	wc_.hInstance = GetModuleHandle(nullptr);

	// カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// 登録する
	RegisterClass(&wc_);


	/*---------------------------
	    ウィンドウサイズを決める
	---------------------------*/

	// ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0 , 0 , clientWidth_ , clientHeight };

	// クライアント領域をもとに、実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


	/*---------------------------
	    ウィンドウを生成して表示
	---------------------------*/

	// ウィンドウの生成
	hwnd_ = CreateWindow(
		// 利用するクラス名
		wc_.lpszClassName,

		// タイトルバーの文字
		title_.c_str(),

		// ウィンドウスタイル
		WS_OVERLAPPEDWINDOW,

		// 表示X座標
		CW_USEDEFAULT,

		// 表示Y座標
		CW_USEDEFAULT,

		// ウィンドウ横幅
		wrc.right - wrc.left,

		// ウィンドウ縦幅
		wrc.bottom - wrc.top,

		// 親ウィンドウハンドル
		nullptr,

		// メニューハンドル
		nullptr,

		// インスタンスハンドル
		wc_.hInstance,

		// オプション
		nullptr
	);

	// ウィンドウを表示する
	ShowWindow(hwnd_, SW_SHOW);
}

/// <summary>
/// ウィンドウにメッセージを渡して応答する
/// </summary>
/// <returns></returns>
bool WinApp::ProcessMessage()
{
	MSG msg{};

	// ウィンドウでxボタンが押されるまでループ
	while (msg.message != WM_QUIT)
	{
		// ウィンドウにメッセージが来ていたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ゲームの処理
			return true;
		}
	}

	// ゲーム終了
	return false;
}