#pragma once
#include <memory>

#include "WinApp/WinApp.h"
#include "LogFile/LogFile.h"
#include "DirectXBase/DirectXBase.h"
#include "Func/CrushHandler/CrushHandler.h"

class MugenEngine
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title);

	/// <summary>
	/// ウィンドウにメッセージを渡して応答する
	/// </summary>
	/// <returns></returns>
	bool ProcessMessage() { return winApp_->ProcessMessage(); }

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw() { directXBase_->PreDraw(); }

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw() { directXBase_->PostDraw(); }


private:

	// クライアント領域横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域縦幅
	const int32_t* kClientHeight_ = nullptr;


	// ログファイル
	std::unique_ptr<LogFile> logFile_ = nullptr;

	// ウィンドウズアプリケーション
	std::unique_ptr<WinApp> winApp_ = nullptr;
	
	// DirectXのベース
	std::unique_ptr<DirectXBase> directXBase_ = nullptr;
};

