#pragma once
#include "../BasePSOPostEffect.h"

class PSOCopyImage : public BasePSOPostEffect
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="vertexShaderBlob"></param>
	/// <param name="pixelShaderBlob"></param>
	/// <param name="device"></param>
	void Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile, 
		IDxcBlob* vertexShaderBlob, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
};

