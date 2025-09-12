#pragma once
#include "DirectXDevice/DirectXDevice.h"

class DirectXBase
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(LogFile* logFile);

	
private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// DirectXデバイス
	std::unique_ptr<DirectXDevice> directXDevice_ = nullptr;
};

