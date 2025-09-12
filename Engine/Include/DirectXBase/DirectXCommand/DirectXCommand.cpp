#include "DirectXCommand.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
void DirectXCommand::Initialize(ID3D12Device* device, LogFile* logFile)
{
	// nullptrチェック
	assert(device);
	assert(logFile);

	// 引数を受け取る
	device_ = device;
	logFile_ = logFile;


	/*---------------------------
	    コマンドキューを生成する
	---------------------------*/

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	HRESULT hr = device_->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue_));
	assert(SUCCEEDED(hr));

	// コマンドキュー生成成功のログ
	logFile_->Log("SUCCEEDED : CommandQueue \n");



	/*-----------------------------
	    コマンドアロケータを生成する
	-----------------------------*/

	hr = device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator_));
	assert(SUCCEEDED(hr));

	// コマンドアロケータ生成成功のログ
	logFile_->Log("SUCCEEDED : CommandAllocator \n");


	/*--------------------------
	    コマンドリストを生成する
	--------------------------*/

	hr = device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator_.Get(), nullptr, IID_PPV_ARGS(&commandList_));
	assert(SUCCEEDED(hr));

	// コマンドリスト生成成功のログ
	logFile_->Log("SUCCEEDED : CommandList \n");
}