#include "PrimitiveResourcesCube.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device"></param>
/// <param name="commandList"></param>
void PrimitiveResourcesCube::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
{
	// 基底クラスを初期化する
	PrimitiveResourcesData::Initialize(device, commandList);

	// インデックスリソースを生成する
	CreateIndexResource(kNumMesh * 6);

	// 頂点リソースを生成する
	CreateVertexResource(kNumMesh * 4);


	/*-----------------------------
	    インデックスの番号を与える
	-----------------------------*/

	// 番号を与える
	for (int32_t i = 0; i < kNumMesh; ++i)
	{
		int32_t startIndex = i * 6;
		int32_t index = i * 4;

		indexData_[startIndex] = index;
		indexData_[startIndex + 1] = index + 1;
		indexData_[startIndex + 2] = index + 2;
		indexData_[startIndex + 3] = index + 1;
		indexData_[startIndex + 4] = index + 3;
		indexData_[startIndex + 5] = index + 2;
	}


	/*------------------------
	    頂点データを入力する
	------------------------*/

	// ローカル座標を与える
	vertexData_[0].position = Vector4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[0].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertexData_[1].position = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[1].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertexData_[2].position = Vector4(1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[2].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertexData_[3].position = Vector4(1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[3].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[3].normal = Vector3(0.0f, 0.0f, -1.0f);

	vertexData_[4].position = Vector4(1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[4].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[4].normal = Vector3(1.0f, 0.0f, 0.0f);
	vertexData_[5].position = Vector4(1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[5].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[5].normal = Vector3(1.0f, 0.0f, 0.0f);
	vertexData_[6].position = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[6].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[6].normal = Vector3(1.0f, 0.0f, 0.0f);
	vertexData_[7].position = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[7].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[7].normal = Vector3(1.0f, 0.0f, 0.0f);

	vertexData_[8].position = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[8].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[8].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData_[9].position = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[9].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[9].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData_[10].position = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[10].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[10].normal = Vector3(0.0f, 0.0f, 1.0f);
	vertexData_[11].position = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[11].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[11].normal = Vector3(0.0f, 0.0f, 1.0f);

	vertexData_[12].position = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[12].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[12].normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertexData_[13].position = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[13].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[13].normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertexData_[14].position = Vector4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[14].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[14].normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertexData_[15].position = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[15].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[15].normal = Vector3(-1.0f, 0.0f, 0.0f);

	vertexData_[16].position = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[16].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[16].normal = Vector3(0.0f, 1.0f, 0.0f);
	vertexData_[17].position = Vector4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[17].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[17].normal = Vector3(0.0f, 1.0f, 0.0f);
	vertexData_[18].position = Vector4(1.0f, 1.0f, -1.0f, 1.0f);
	vertexData_[18].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[18].normal = Vector3(0.0f, 1.0f, 0.0f);
	vertexData_[19].position = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexData_[19].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[19].normal = Vector3(0.0f, 1.0f, 0.0f);

	vertexData_[20].position = Vector4(1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[20].texcoord = Vector2(0.0f, 1.0f);
	vertexData_[20].normal = Vector3(0.0f, -1.0f, 0.0f);
	vertexData_[21].position = Vector4(1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[21].texcoord = Vector2(0.0f, 0.0f);
	vertexData_[21].normal = Vector3(0.0f, -1.0f, 0.0f);
	vertexData_[22].position = Vector4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertexData_[22].texcoord = Vector2(1.0f, 1.0f);
	vertexData_[22].normal = Vector3(0.0f, -1.0f, 0.0f);
	vertexData_[23].position = Vector4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertexData_[23].texcoord = Vector2(1.0f, 0.0f);
	vertexData_[23].normal = Vector3(0.0f, -1.0f, 0.0f);
}

/// <summary>
/// コマンドリストに登録する
/// </summary>
void PrimitiveResourcesCube::Register()
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