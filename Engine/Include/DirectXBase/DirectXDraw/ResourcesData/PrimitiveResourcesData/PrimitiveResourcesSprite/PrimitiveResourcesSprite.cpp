#include "PrimitiveResourcesSprite.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void PrimitiveResourcesSprite::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// 基底クラスの初期化
	PrimitiveResourcesData::Initialize(device, commandList);

	// インデックスリソースを生成する
	CreateIndexResource(6);

	// 頂点リソースを生成する
	CreateVertexResource(4);


	/*------------------------------
	    インデックスの番号を入力する
	------------------------------*/

	// 番号を割り当てる
	indexData_[0] = 0;
	indexData_[1] = 1;
	indexData_[2] = 2;
	indexData_[3] = 1;
	indexData_[4] = 3;
	indexData_[5] = 2;


	/*------------------------
	    頂点データを入力する
	------------------------*/

	// 左下
	vertexData_[0].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[0].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[0].normal = Vector3(0.0f, 0.0f, -1.0f);

	// 左上
	vertexData_[1].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[1].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[1].normal = Vector3(0.0f, 0.0f, -1.0f);

	// 右下
	vertexData_[2].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[2].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[2].normal = Vector3(0.0f, 0.0f, -1.0f);

	// 右上
	vertexData_[3].position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexData_[3].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[3].normal = Vector3(0.0f, 0.0f, -1.0f);


	// ライティングは無効にする
	materialData_->enableLighting_ = false;
	materialData_->enableHalfLambert_ = false;
}

/// <summary>
/// コマンドリストに登録する
/// </summary>
void PrimitiveResourcesSprite::Register()
{
	// インデックスリソースの設定
	commandList_->IASetIndexBuffer(&indexBufferView_);

	// 頂点リソースの設定
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView_);

	// マテリアルリソースの設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// 座標変換リソースの設定
	commandList_->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
}