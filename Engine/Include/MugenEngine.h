#pragma once
#include "WinApp/WinApp.h"
#include <memory>

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


private:

	// ウィンドウズアプリケーション
	std::unique_ptr<WinApp> winApp_ = nullptr;
	
};

