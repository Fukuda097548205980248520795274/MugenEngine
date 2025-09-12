#include "DirectXBase.h"

/// <summary>
/// 初期化
/// </summary>
void DirectXBase::Initialize(LogFile* logFile)
{
	// nullptrチェック
	assert(logFile);

	// 引数を受け取る
	logFile_ = logFile;

	// DirectXデバイスの生成と初期化
	directXDevice_ = std::make_unique<DirectXDevice>();
	directXDevice_->Initialize(logFile_);
}