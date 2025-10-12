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
	blendMode_ = static_cast<int>(BlendMode::kAdd);


	// 頂点シェーダのバイナリデータを取得する
	vertexShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Resources/Shader/Particle/Particle.VS.hlsl", L"vs_6_0");
	assert(vertexShaderBlob_ != nullptr);

	// ピクセルシェーダのバイナリデータを取得する
	pixelShaderBlob_ = directXShaderCompile_->CompilerShader(L"./Resources/Shader/Particle/Particle.PS.hlsl", L"ps_6_0");
	assert(pixelShaderBlob_ != nullptr);

	// Shaderを読み込めた旨のログを出力
	logFile_->Log("SUCCEEDED : ParticleShader\n");


	// PSOの生成と初期化
	// 合成なし
	pso_[static_cast<int>(BlendMode::kNone)] = std::make_unique<SinglePSOParticleNone>();
	pso_[static_cast<int>(BlendMode::kNone)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// ノーマル
	pso_[static_cast<int>(BlendMode::kNormal)] = std::make_unique<SinglePSOParticleNormal>();
	pso_[static_cast<int>(BlendMode::kNormal)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// 加算合成
	pso_[static_cast<int>(BlendMode::kAdd)] = std::make_unique<SinglePSOParticleAdd>();
	pso_[static_cast<int>(BlendMode::kAdd)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// 減算合成
	pso_[static_cast<int>(BlendMode::kSubtract)] = std::make_unique<SinglePSOParticleSubtract>();
	pso_[static_cast<int>(BlendMode::kSubtract)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// 乗算合成
	pso_[static_cast<int>(BlendMode::kMultiply)] = std::make_unique<SinglePSOParticleMultiply>();
	pso_[static_cast<int>(BlendMode::kMultiply)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);

	// スクリーン合成
	pso_[static_cast<int>(BlendMode::kScreen)] = std::make_unique<SinglePSOParticleScreen>();
	pso_[static_cast<int>(BlendMode::kScreen)]->Initialize(logFile_, vertexShaderBlob_.Get(), pixelShaderBlob_.Get(), device_, commandList_);
}