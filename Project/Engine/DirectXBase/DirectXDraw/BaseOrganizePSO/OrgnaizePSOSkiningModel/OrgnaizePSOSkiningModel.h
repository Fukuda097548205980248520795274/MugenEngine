#pragma once
#include "../BaseOrganizePSO.h"
#include "../EnumBlendMode/EnumBlendMode.h"
#include "SinglePSOSkiningModelNormal/SinglePSOSkiningModelNormal.h"

class OrgnaizePSOSkiningModel : public BaseOrganizePSO
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
	void SetPSOState() override { pso_->SetPSOState(); }

	/// <summary>
	/// ブレンドモードをリセットする
	/// </summary>
	void ResetBlendMode() override {  }


private:

	// PSO
	std::unique_ptr<BaseSinglePSO> pso_ = { nullptr };
};

