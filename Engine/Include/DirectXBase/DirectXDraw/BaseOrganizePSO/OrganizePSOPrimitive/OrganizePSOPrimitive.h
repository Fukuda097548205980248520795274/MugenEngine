#pragma once
#include "../BaseOrganizePSO.h"
#include "../EnumBlendMode/EnumBlendMode.h"
#include "SinglePSOPrimitiveNone/SinglePSOPrimitiveNone.h"
#include "SinglePSOPrimitiveNormal/SinglePSOPrimitiveNormal.h"

class OrganizePSOPrimitive : public BaseOrganizePSO
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="logFile"></param>
	/// <param name="directXCompile"></param>
	void Initialize(LogFile* logFile, DirectXShaderCompile* directXShaderCompile,
		ID3D12GraphicsCommandList* commandList, ID3D12Device* device) override;

	/// <summary>
	/// PSOの設定をコマンドリストの登録する
	/// </summary>
	void SetPSOState() override { pso_[blendMode_]->SetPSOState(); }

	/// <summary>
	/// ブレンドモードのSetter
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendMode(BlendMode blendMode) { blendMode_ = static_cast<int>(blendMode); }


private:

	// PSO
	std::unique_ptr<BaseSinglePSO> pso_[static_cast<int>(BlendMode::kNumBlendMode)] = { nullptr };

	// 現在のブレンドモード
	int blendMode_ = static_cast<int>(BlendMode::kNormal);
};

