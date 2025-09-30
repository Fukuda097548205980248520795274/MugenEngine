#include "DirectXFence.h"

/// <summary>
/// デストラクタ
/// </summary>
DirectXFence::~DirectXFence()
{
	// イベントハンドルを閉じる
	CloseHandle(fenceEvent_);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
void DirectXFence::Initialize(LogFile* logFile, ID3D12Device* device)
{
	// nullptrチェック
	assert(device);
	assert(logFile);


	/*------------------
	    フェンスの生成
	------------------*/

	HRESULT hr = device->CreateFence(fenceValue_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	assert(SUCCEEDED(hr));

	// フェンス生成成功のログ
	logFile->Log("SUCCEEDED : Fence \n");



	/*-------------------
	    イベントの生成
	-------------------*/

	fenceEvent_ = CreateEvent(NULL, FALSE, FALSE, NULL);
	assert(fenceEvent_ != nullptr);

	// イベント生成成功のログ
	logFile->Log("SUCCEEDED : Event \n");
}


/// <summary>
/// シグナルを送る
/// </summary>
void DirectXFence::SnedSignal(ID3D12CommandQueue* commandQueue)
{
	// フェンスの値を更新
	fenceValue_++;

	// GPUがここまでたどり着いた時に、Fenceの値を、指定した値に代入するようにシグナルを送る
	commandQueue->Signal(fence_.Get(), fenceValue_);
}

/// <summary>
/// GPUを待つ
/// </summary>
void DirectXFence::WaitGPU()
{
	// フェンスの値が指定したシグナル値にたどりついているか確認する
	if (fence_->GetCompletedValue() < fenceValue_)
	{
		// 指定したシグナル値にたどり着いていないので、たどり着くまで待つようにイベントを設定する
		fence_->SetEventOnCompletion(fenceValue_, fenceEvent_);

		// イベントを待つ
		WaitForSingleObject(fenceEvent_, INFINITE);
	}
}