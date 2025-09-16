#include "OrganizePSOPrimitive.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="directXShaderCompile"></param>
void OrganizePSOPrimitive::Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile,
	ID3D12GraphicsCommandList* commandList, ID3D12Device* device)
{
	// 基底クラスの初期化
	BaseOrganizePSO::Initialize(logFile, directXShaderCompile, commandList, device);


	// 頂点シェーダのバイナリデータを取得する
	vertexShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Engine/Shader/Primitive/Primitive.VS.hlsl", L"vs_6_0");
	assert(vertexShaderBlob_ != nullptr);

	// ピクセルシェーダのバイナリデータを取得する
	pixelShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Engine/Shader/Primitive/Primitive.PS.hlsl", L"ps_6_0");
	assert(pixelShaderBlob_ != nullptr);

	// Shaderを読み込めた旨のログを出力
	logFile_->Log("SUCCEEDED : PrimitiveShader\n");


	// PSOの生成と初期化
	pso_ = std::make_unique<SinglePSOPrimitiveNone>();
	pso_->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);
}