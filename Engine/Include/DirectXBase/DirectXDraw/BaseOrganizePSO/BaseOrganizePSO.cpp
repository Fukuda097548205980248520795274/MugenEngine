#include "BaseOrganizePSO.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="directXCompile"></param>
void BaseOrganizePSO::Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile,
	ID3D12GraphicsCommandList* commandList, ID3D12Device* device)
{
	// nullptrチェック
	assert(logFile);
	assert(directXShaderCompile);
	assert(commandList);
	assert(device);

	// 引数を受け取る
	logFile_ = logFile;
	directXShaderCompile_ = directXShaderCompile;
	commandList_ = commandList;
	device_ = device;
}