#pragma once
#include "../PrimitiveResourcesData.h"

class PrimitiveResourcesUVSphere : public PrimitiveResourcesData
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	/// <param name="commandList"></param>
	void Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)override;

	/// <summary>
	/// コマンドリストに登録する
	/// </summary>
	void Register()override;

	/// <summary>
	/// セグメント最大数のGetter
	/// </summary>
	/// <returns></returns>
	const int32_t GetMaxSegment()const { return kMaxSegment; };

	/// <summary>
	/// セグメント最小数のGetter
	/// </summary>
	/// <returns></returns>
	const int32_t GetMinSegment()const { return kMinSegment; }

	/// <summary>
	/// セグメント最大数のGetter
	/// </summary>
	/// <returns></returns>
	const int32_t GetMaxRing()const { return kMaxRing; };

	/// <summary>
	/// セグメント最小数のGetter
	/// </summary>
	/// <returns></returns>
	const int32_t GetMinRing()const { return kMinRing; }


private:

	// 最大セグメント数
	const int32_t kMaxSegment = 32;

	// 最小セグメント数
	const int32_t kMinSegment = 3;


	// 最大リング数
	const int32_t kMaxRing = 16;

	// 最小リング数
	const int32_t kMinRing = 3;
};

