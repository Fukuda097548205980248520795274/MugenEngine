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
		const std::string& fileDirectory, const std::string& fileName, const std::string& extName, ModelHandle modelHandle) override;

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
	/// ボーンのアニメーションを再生する
	/// </summary>
	void ApplyBoneAnimation(float animationTiemer) override { ApplayBoneAnimation(skeleton_, animation_, animationTiemer); }

	/// <summary>
	/// ボーンの更新処理
	/// </summary>
	void UpdateBone() override { UpdateSkeleton(skeleton_); }

	/// <summary>
	/// MatrixPaletteを更新する
	/// </summary>
	/// <param name="meshIndex"></param>
	void UpdateMatrixPalette(const std::string& meshName) override { UpdateSkinCluster(modelData_.meshData[meshName].skinCluster, skeleton_); }


public:

	// DirectXヒープ
	DirectXHeap* directXHeap_ = nullptr;
};

