#pragma once
#include "../BaseModelResources.h"

class GltfModelResources : public BaseModelResources
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device_"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, TextureStore* textureStore,
		const std::string& fileDirectory, const std::string& fileName, const std::string& extName, uint32_t modelHandle) override;

	/// <summary>
	/// DirectXヒープのSetter
	/// </summary>
	/// <param name="directXHeap"></param>
	void SetDirectXHeap(DirectXHeap* directXHeap) { directXHeap_ = directXHeap; }

	/// <summary>
	/// 頂点とインデックスをコマンドリストに登録する
	/// </summary>
	/// <param name="meshIndex"></param>
	void Register(uint32_t meshIndex) override;

	/// <summary>
	/// ルートノードのGetter
	/// </summary>
	/// <returns></returns>
	Node GetRootNode()const override { return rootNode_; }


public:

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;


	// ルートノード
	Node rootNode_{};

	// アニメーション
	Animation animation_{};

	// スケルトン
	Skeleton skeleton_{};
};

