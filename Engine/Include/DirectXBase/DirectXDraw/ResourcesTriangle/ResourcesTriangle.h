#pragma once
#include <cassert>

#include "../../../Func/CreateBufferResource/CreateBufferResource.h"
#include "../VertexData/VertexData.h"
#include "../../../Math/Matrix4x4/Matrix4x4.h"

class ResourcesTriangle
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// コマンドリストに設定を登録する
	/// </summary>
	void SetCommandList();


	// 頂点データ
	VertexData* vertexData_ = nullptr;

	// マテリアルデータ
	Vector4* materialData_ = nullptr;

	// 座標変換データ
	Matrix4x4* transformationData_ = nullptr;

	
private:

	// デバイス
	ID3D12Device* device_ = nullptr;

	// コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;


	// 頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};


	// マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;


	// 座標変換リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource_ = nullptr;
};

