#include "BaseSinglePSO.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="vertexShaderBlob"></param>
/// <param name="pixelShaderBlob"></param>
/// <param name="device"></param>
void BaseSinglePSO::Initialize(LogFile* logFile, IDxcBlob* vertexShaderBlob, IDxcBlob* pixelShaderBlob,
	ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(logFile);
	assert(vertexShaderBlob);
	assert(pixelShaderBlob);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	logFile_ = logFile;
	vertexShaderBlob_ = vertexShaderBlob;
	pixelShaderBlob_ = pixelShaderBlob;
	device_ = device;
	commandList_ = commandList;
}

/// <summary>
/// PSOをコマンドリストのセットする
/// </summary>
void BaseSinglePSO::SetPSOState()
{
	commandList_->SetGraphicsRootSignature(rootSignature_.Get());
	commandList_->SetPipelineState(graphicsPipelineState_.Get());
}