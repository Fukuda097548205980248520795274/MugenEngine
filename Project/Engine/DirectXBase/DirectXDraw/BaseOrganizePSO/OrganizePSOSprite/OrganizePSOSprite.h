#pragma once
#include "../BaseOrganizePSO.h"
#include "../EnumBlendMode/EnumBlendMode.h"
#include "SinglePSOSpriteAdd/SinglePSOSpriteAdd.h"
#include "SinglePSOSpriteMultiply/SinglePSOSpriteMultiply.h"
#include "SinglePSOSpriteNone/SinglePSOSpriteNone.h"
#include "SinglePSOSpriteNormal/SinglePSOSpriteNormal.h"
#include "SinglePSOSpriteScreen/SinglePSOSpriteScreen.h"
#include "SinglePSOSpriteSubtract/SinglePSOSpriteSubtract.h"

class OrganizePSOSprite : public BaseOrganizePSO
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
	/// ブレンドモードをリセットする
	/// </summary>
	void ResetBlendMode() override { blendMode_ = static_cast<int>(BlendMode::kNormal); }


private:

	// PSO
	std::unique_ptr<BaseSinglePSO> pso_[static_cast<int>(BlendMode::kNumBlendMode)] = { nullptr };
};

