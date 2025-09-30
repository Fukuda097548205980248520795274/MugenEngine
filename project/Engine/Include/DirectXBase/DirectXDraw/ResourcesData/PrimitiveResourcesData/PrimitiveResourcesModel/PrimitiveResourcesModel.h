#pragma once
#include "../../../../../Func/CreateBufferResource/CreateBufferResource.h"

#include "../../../DataForGPU/VertexData/VertexData.h"
#include "../../../DataForGPU/MaterialData/MaterialData.h"
#include "../../../DataForGPU/TransformationData/TransformationData.h"

class PrimitiveResourcesModel
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	/// <param name="indexNum"></param>
	/// <param name="vertexNum"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, uint32_t indexNum, uint32_t vertexNum);


private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	// インデックス数
	uint32_t indexNum_ = 0;

	// 頂点数
	uint32_t vertexNum_ = 0;
};

