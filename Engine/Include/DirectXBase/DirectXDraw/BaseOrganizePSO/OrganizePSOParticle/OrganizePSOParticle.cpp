#include "OrganizePSOParticle.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="logFile"></param>
/// <param name="directXShaderCompile"></param>
void OrganizePSOParticle::Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile,
	ID3D12GraphicsCommandList* commandList, ID3D12Device* device)
{
	// 基底クラスの初期化
	BaseOrganizePSO::Initialize(logFile, directXShaderCompile, commandList, device);

	// 初期ブレンドモード
	blendMode_ = static_cast<int>(BlendMode::kNormal);


	// 頂点シェーダのバイナリデータを取得する
	vertexShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Engine/Shader/Particle/Particle.VS.hlsl", L"vs_6_0");
	assert(vertexShaderBlob_ != nullptr);

	// ピクセルシェーダのバイナリデータを取得する
	pixelShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Engine/Shader/Particle/Particle.PS.hlsl", L"ps_6_0");
	assert(pixelShaderBlob_ != nullptr);


	// ノーマル
	pso_[static_cast<int>(BlendMode::kNormal)] = std::make_unique<SinglePSOParticleNormal>();
	pso_[static_cast<int>(BlendMode::kNormal)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);


	// Shaderを読み込めた旨のログを出力
	logFile_->Log("SUCCEEDED : ParticleShader\n");
}