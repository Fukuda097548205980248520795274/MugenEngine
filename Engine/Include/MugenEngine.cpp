#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void MugenEngine::Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title)
{
	// 出力用のディレクトリを掘る
	std::filesystem::create_directories("./Engine/Output");

	// 例外が発生したときに起動する
	SetUnhandledExceptionFilter(ExportDump);

	// ログファイルの生成と初期化
	logFile_ = std::make_unique<LogFile>();
	logFile_->Initialize();

	// ウィンドウアプリケーションの生成と初期化
	winApp_ = std::make_unique<WinApp>();
	winApp_->Initialize(clientWidth, clientHeight, title);

	// DirectXベースの生成と初期化
	directXBase_ = std::make_unique<DirectXBase>();
	directXBase_->Initialize(logFile_.get());
}