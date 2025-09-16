#pragma once
#include <memory>
#include <dxgidebug.h>

#include "WinApp/WinApp.h"
#include "LogFile/LogFile.h"
#include "DirectXBase/DirectXBase.h"
#include "Func/CrushHandler/CrushHandler.h"

class MugenEngine
{
public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MugenEngine();

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

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath)const { return directXBase_->LoadTexture(filePath); }

	// 三角形を描画する
	void DrawTriangle(uint32_t textureHandle)const { directXBase_->DrawTrinagle(textureHandle); }


private:

	// クライアント領域横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域縦幅
	const int32_t* kClientHeight_ = nullptr;


	// ログファイル
	LogFile* logFile_ = nullptr;

	// ウィンドウズアプリケーション
	WinApp* winApp_ = nullptr;
	
	// DirectXのベース
	DirectXBase* directXBase_ = nullptr;
};

