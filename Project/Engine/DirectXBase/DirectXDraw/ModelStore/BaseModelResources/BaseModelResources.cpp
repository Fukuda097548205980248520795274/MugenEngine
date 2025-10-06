#include "BaseModelResources.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="device_"></param>
/// <param name="commandList"></param>
void BaseModelResources::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, TextureStore* textureStore,
	const std::string& fileDirectory, const std::string& fileName, const std::string& extName, uint32_t modelHandle)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(textureStore);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	textureStore_ = textureStore;
	extName_ = extName;
	modelHandle_ = modelHandle;
	filePath_ = fileDirectory + "/" + fileName;

	
}
