#pragma once
#include "../../BaseSinglePSO/BaseSinglePSO.h"

class SinglePSOPrimitiveMultiply : public BaseSinglePSO
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="vertexShaderBlob"></param>
	/// <param name="pixelShaderBlob"></param>
	/// <param name="device"></param>
	void Initialize(LogFile* logFile, IDxcBlob* vertexShaderBlob, IDxcBlob* pixelShaderBlob,
		ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
};

