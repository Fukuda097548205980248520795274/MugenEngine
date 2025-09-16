#pragma once
#include "../BaseOrganizePSO.h"
#include "SinglePSOSpriteNone/SinglePSOSpriteNone.h"

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
	void SetPSOState() override { pso_->SetPSOState(); }


private:

	// PSO
	std::unique_ptr<BaseSinglePSO> pso_ = nullptr;
};

