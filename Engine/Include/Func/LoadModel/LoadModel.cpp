#include "LoadModel.h"


/// <summary>
/// mtlファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
	// ファイルを開く
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());

	// 構築するマテリアルデータ
	MaterialData materialData;

	// 1行
	std::string line;

	while (std::getline(file, line))
	{
		std::string identifier;
		std::stringstream s(line);
		s >> identifier;

		// identifierに応じた処理
		if (identifier == "map_Kd")
		{
			std::string textureFilename;
			s >> textureFilename;

			// 連結してファイルパスにする
			materialData.textureFilePath = directoryPath + "/" + textureFilename;
		}
	}

	return materialData;
}


/// <summary>
/// オブジェファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
std::vector<ModelData> LoadObjFile(const std::string& directoryPath, const std::string& filename)
{
	// assimpでファイルを開く
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;

	// シーンのデータ
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	// メッシュがないのは対応しない
	assert(scene->HasMeshes());

	// モデルデータ
	std::vector<ModelData> modelData;

	// 頂点データ
	Vector4 position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	Vector3 normal = Vector3(0.0f, 0.0f, 0.0f);
	Vector2 texcoord = Vector2(0.0f, 0.0f);


	// メッシュ
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
	{
		// モデルデータ
		ModelData modelDatum;

		// メッシュのデータ
		aiMesh* mesh = scene->mMeshes[meshIndex];

		// 法線がないメッシュは非対応
		assert(mesh->HasNormals());

		// UV座標がないのは非対応
		assert(mesh->HasTextureCoords(0));

		// 頂点データを登録する
		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			// 頂点データを取得する
			aiVector3D& position = mesh->mVertices[i];
			aiVector3D& normal = mesh->mNormals[i];
			aiVector3D& texcoord = mesh->mTextureCoords[0][i];

			// 値を取得する
			VertexDataForGPU vertex;
			vertex.position = Vector4(position.x, position.y, position.z, 1.0f);
			vertex.normal = Vector3(normal.x, normal.y, normal.z);
			vertex.texcoord = Vector2(texcoord.x, texcoord.y);

			// 右手から左手に変換
			vertex.position.x *= -1.0f;
			vertex.normal.x *= -1.0f;

			// データに登録
			modelDatum.vertices.push_back(vertex);
		}

		// インデックスデータを登録する
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			// フェイスのデータ
			aiFace& face = mesh->mFaces[faceIndex];

			// 三角形のみサポート
			assert(face.mNumIndices == 3);

			// インデックスを登録
			for (uint32_t i = 0; i < face.mNumIndices; ++i)
			{
				modelDatum.indices.push_back(face.mIndices[i]);
			}
		}


		// マテリアルインデックス
		uint32_t materialIndex = mesh->mMaterialIndex;

		// マテリアルデータ
		aiMaterial* material = scene->mMaterials[materialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)
		{
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			modelDatum.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
		}

		// 登録する
		modelData.push_back(modelDatum);
	}

	return modelData;
}