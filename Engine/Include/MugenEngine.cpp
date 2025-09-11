#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void MugenEngine::Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title)
{
	// ウィンドウアプリケーションの生成と初期化
	winApp_ = std::make_unique<WinApp>();
	winApp_->Initialize(clientWidth, clientHeight, title);
}