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
/// ノードにワールド行列を生成する
/// </summary>
/// <param name="node"></param>
/// <param name="parentWorldMatrix"></param>
void NodeWorldMatrix(Node& node, const Matrix4x4& parentWorldMatrix)
{
	// ワールド行列
	node.worldMatrix = parentWorldMatrix * node.localMatrix;

	// 再帰処理で子ノードに対して処理
	for (Node& child : node.children)
	{
		NodeWorldMatrix(child, node.worldMatrix);
	}
}

/// <summary>
/// ノード情報を取得する
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
Node GetReadNode(const std::string& directoryPath, const std::string& filename)
{
	// assimpでファイルを開く
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;

	// シーンのデータ
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	return ReadNode(scene->mRootNode);
}

/// <summary>
/// ノード情報を読む
/// </summary>
/// <param name="node"></param>
/// <returns></returns>
Node ReadNode(aiNode* node)
{
	// 総括
	Node result;

	// ノードのローカル行列を取得する
	aiMatrix4x4 aiLocalMatrix = node->mTransformation;

	// 列ベクトルを行ベクトルに転置する
	aiLocalMatrix.Transpose();

	result.localMatrix.m[0][0] = aiLocalMatrix[0][0];
	result.localMatrix.m[0][1] = aiLocalMatrix[0][1];
	result.localMatrix.m[0][2] = aiLocalMatrix[0][2];
	result.localMatrix.m[0][3] = aiLocalMatrix[0][3];

	result.localMatrix.m[1][0] = aiLocalMatrix[1][0];
	result.localMatrix.m[1][1] = aiLocalMatrix[1][1];
	result.localMatrix.m[1][2] = aiLocalMatrix[1][2];
	result.localMatrix.m[1][3] = aiLocalMatrix[1][3];

	result.localMatrix.m[2][0] = aiLocalMatrix[2][0];
	result.localMatrix.m[2][1] = aiLocalMatrix[2][1];
	result.localMatrix.m[2][2] = aiLocalMatrix[2][2];
	result.localMatrix.m[2][3] = aiLocalMatrix[2][3];

	result.localMatrix.m[3][0] = aiLocalMatrix[3][0];
	result.localMatrix.m[3][1] = aiLocalMatrix[3][1];
	result.localMatrix.m[3][2] = aiLocalMatrix[3][2];
	result.localMatrix.m[3][3] = aiLocalMatrix[3][3];

	// ノード名を格納
	result.name = node->mName.C_Str();

	// 子供の数だけ確保
	result.children.resize(node->mNumChildren);

	// 再帰的に読んで階層構造を作っていく
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; ++childIndex)
	{
		result.children[childIndex] = ReadNode(node->mChildren[childIndex]);
	}

	return result;
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
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices |
		aiProcess_RemoveRedundantMaterials);

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

/// <summary>
/// ノードのワールド行列
/// </summary>
/// <param name="rootNode"></param>
/// <returns></returns>
void GetNodeWorldMatrix(std::vector<Matrix4x4>& worldMatrices, const Node& rootNode)
{
	worldMatrices.push_back(rootNode.worldMatrix);

	for (const Node& node : rootNode.children)
	{
		GetNodeWorldMatrix(worldMatrices, node);
	}
}


/// <summary>
/// アニメーションファイルを読み込む
/// </summary>
/// <param name="directoryPath"></param>
/// <param name="filename"></param>
/// <returns></returns>
Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename)
{
	Animation animation;

	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);

	// アニメーションがないといけいない
	assert(scene->mNumAnimations != 0);

	// 最初のアニメーションだけ採用
	aiAnimation* animationAssimp = scene->mAnimations[0];

	// 時間の単位を秒に変換
	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);

	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex)
	{
		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];

		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];

		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; ++keyIndex)
		{
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];

			KeyFrameVector3 keyframe;

			// 秒に変換
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);

			// 右手 -> 左手
			keyframe.value = { -keyAssimp.mValue.x, keyAssimp.mValue.y,keyAssimp.mValue.z };
			nodeAnimation.translate.push_back(keyframe);
		}

		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; ++keyIndex)
		{
			aiQuatKey& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];

			KeyFrameQuaternion keyframe;

			// 秒に変換
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);

			// 右手 -> 左手
			keyframe.value = { keyAssimp.mValue.x, -keyAssimp.mValue.y, -keyAssimp.mValue.z , keyAssimp.mValue.w };
			nodeAnimation.rotate.push_back(keyframe);
		}

		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumScalingKeys; ++keyIndex)
		{
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];

			KeyFrameVector3 keyframe;

			// 秒に変換
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);

			// そのまま
			keyframe.value = { keyAssimp.mValue.x, keyAssimp.mValue.y,keyAssimp.mValue.z };
			nodeAnimation.scale.push_back(keyframe);
		}
	}

	return animation;
}