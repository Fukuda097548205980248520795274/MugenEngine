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


	// スプライトを描画する
	void DrawSprite(const WorldTransform2D* worldTransform, const Camera2D* camera, uint32_t textureHandle)const
	{ directXBase_->DrawSprite(worldTransform,camera, textureHandle); }

	/// <summary>
	/// UV球を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="segment"></param>
	/// <param name="ring"></param>
	void DrawUVSphere(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle,
		int32_t segment, int32_t ring) const
	{directXBase_->DrawUVSphere(worldTransform, camera, textureHandle, segment, ring);}

	/// <summary>
	/// 立方体を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	void DrawCube(const WorldTransform3D* worldTransform, const Camera3D* camera, uint32_t textureHandle) const
	{directXBase_->DrawCube(worldTransform, camera, textureHandle);}


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

