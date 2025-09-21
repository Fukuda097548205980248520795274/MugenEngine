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

	// 初期ブレンドモード
	blendMode_ = static_cast<int>(BlendMode::kNormal);


	// 頂点シェーダのバイナリデータを取得する
	vertexShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Engine/Shader/Primitive/Primitive.VS.hlsl", L"vs_6_0");
	assert(vertexShaderBlob_ != nullptr);

	// ピクセルシェーダのバイナリデータを取得する
	pixelShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Engine/Shader/Primitive/Primitive.PS.hlsl", L"ps_6_0");
	assert(pixelShaderBlob_ != nullptr);

	// Shaderを読み込めた旨のログを出力
	logFile_->Log("SUCCEEDED : PrimitiveShader\n");


	// PSOの生成と初期化
	// 合成なし
	pso_[static_cast<int>(BlendMode::kNone)] = std::make_unique<SinglePSOPrimitiveNone>();
	pso_[static_cast<int>(BlendMode::kNone)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// ノーマル
	pso_[static_cast<int>(BlendMode::kNormal)] = std::make_unique<SinglePSOPrimitiveNormal>();
	pso_[static_cast<int>(BlendMode::kNormal)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// 加算合成
	pso_[static_cast<int>(BlendMode::kAdd)] = std::make_unique<SinglePSOPrimitiveAdd>();
	pso_[static_cast<int>(BlendMode::kAdd)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// 減算合成
	pso_[static_cast<int>(BlendMode::kSubtract)] = std::make_unique<SinglePSOPrimitiveSubtract>();
	pso_[static_cast<int>(BlendMode::kSubtract)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// 乗算合成
	pso_[static_cast<int>(BlendMode::kMultiply)] = std::make_unique<SinglePSOPrimitiveMultiply>();
	pso_[static_cast<int>(BlendMode::kMultiply)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// スクリーン合成
	pso_[static_cast<int>(BlendMode::kScreen)] = std::make_unique<SinglePSOPrimitiveScreen>();
	pso_[static_cast<int>(BlendMode::kScreen)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);
}