#pragma once
#include "DirectXDevice/DirectXDevice.h"
#include "DirectXCommand/DirectXCommand.h"
#include "DirectXHeap/DirectXHeap.h"
#include "DirectXBuffering/DirectXBuffering.h"

class DirectXBase
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(LogFile* logFile, HWND hwnd, const int32_t* kClientWidth, const int32_t* kClientHeight);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	
private:

	// ログファイル
	LogFile* logFile_ = nullptr;

	// ウィンドウハンドル
	HWND hwnd_{};

	// 画面の横幅
	const int32_t* kClientWidth_ = nullptr;

	// 画面の縦幅
	const int32_t* kClientHeight_ = nullptr;


	// コマンドキュー
	ID3D12CommandQueue* commandQueue_ = nullptr;

	// コマンドアロケータ
	ID3D12CommandAllocator* commandAllocator_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;




	// DirectXデバイス
	std::unique_ptr<DirectXDevice> directXDevice_ = nullptr;
	
	// DirectXコマンド
	std::unique_ptr<DirectXCommand> directXCommand_ = nullptr;

	// DirectXヒープ
	std::unique_ptr<DirectXHeap> directXHeap_ = nullptr;
	
	// DirectXバッファリング
	std::unique_ptr<DirectXBuffering> directXBuffering_ = nullptr;
};

