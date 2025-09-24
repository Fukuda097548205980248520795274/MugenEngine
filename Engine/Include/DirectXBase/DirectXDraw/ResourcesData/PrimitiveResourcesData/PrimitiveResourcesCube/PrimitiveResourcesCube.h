#pragma once
#include "../PrimitiveResourcesData.h"

class PrimitiveResourcesCube : public PrimitiveResourcesData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	void Register() override;


private:

	// 面の数
	const int32_t kNumMesh = 6;
};

