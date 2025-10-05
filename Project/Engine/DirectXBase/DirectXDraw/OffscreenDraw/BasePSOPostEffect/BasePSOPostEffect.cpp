#include "BasePSOPostEffect.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="vertexShaderBlob"></param>
/// <param name="pixelShaderBlob"></param>
/// <param name="device"></param>
void BasePSOPostEffect::Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile, IDxcBlob* vertexShaderBlob, ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// nullptrチェック
	assert(logFile);
	assert(directXShaderCompile);
	assert(vertexShaderBlob);
	assert(device);
	assert(commandList);

	// 引数を受け取る
	logFile_ = logFile;
	directXShaderCompile_ = directXShaderCompile;
	vertexShaderBlob_ = vertexShaderBlob;
	device_ = device;
	commandList_ = commandList;
}

/// <summary>
/// PSOをコマンドリストのセットする
/// </summary>
void BasePSOPostEffect::RegisterPSO()
{
	commandList_->SetGraphicsRootSignature(rootSignature_.Get());
	commandList_->SetPipelineState(graphicsPipelineState_.Get());
}