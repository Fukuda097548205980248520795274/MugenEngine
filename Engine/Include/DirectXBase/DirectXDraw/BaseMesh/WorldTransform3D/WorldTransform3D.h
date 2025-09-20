#pragma once
#include "../../../../Math/Matrix4x4/Matrix4x4.h"

// 3Dワールドトランスフォーム
class WorldTransform3D
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 親ワールド行列のSetter
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform3D* parent) { parent_ = parent; };

	/// <summary>
	/// ワールド座標のGetter
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition() const;

	// 拡縮
	Vector3 scale_{};

	// 回転
	Vector3 rotation_{};

	// 移動
	Vector3 translation_{};

	// ワールド行列
	Matrix4x4 worldMatrix_{};


private:

	// 親ワールドトランスフォーム
	const WorldTransform3D* parent_ = nullptr;
};
