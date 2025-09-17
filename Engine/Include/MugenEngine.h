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
	/// スクリーン横幅のGetter
	/// </summary>
	/// <returns></returns>
	int32_t GetScreenWidth()const { return winApp_->GetClientWidth(); }

	/// <summary>
	/// スクリーン縦幅のGetter
	/// </summary>
	/// <returns></returns>
	int32_t GetScreenHeight()const { return winApp_->GetClientHeight(); }

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadTexture(const std::string& filePath)const { return directXBase_->LoadTexture(filePath); }

	// 三角形を描画する
	void DrawTriangle(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle)const
	{ directXBase_->DrawTrinagle(worldTransform,camera, textureHandle); }

	// スプライトを描画する
	void DrawSprite(const WorldTransform2D* worldTransform, const Camera2D* camera, uint32_t textureHandle)const
	{ directXBase_->DrawSprite(worldTransform,camera, textureHandle); }


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

