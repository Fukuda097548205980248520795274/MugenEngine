#pragma once
#include <cassert>
#include "../../BaseMesh/Transform/Transform.h"
#include "../../../../Math/Vector4/Vector4.h"

// 前方宣言
class MugenEngine;

class Particle
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const MugenEngine* engine, const Vector3& scale, const Vector3& rotation, const Vector3& translation,
		float speed, const Vector3& velocity, float lifeTime);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 終了フラグのGetter
	/// </summary>
	/// <returns></returns>
	bool IsFinished()const { return IsFinished_; }


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;


	// トランスフォーム
	Transform3D transform_;


	// 速度
	float speed_ = 0.0f;

	// 移動
	Vector3 velocity_;


	// 色
	Vector4 color_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);


	// 生存タイマー
	float lifeTimer_ = 0.0f;

	// 生存時間
	float lifeTime_ = 0.0f;


	// 終了フラグ
	bool IsFinished_ = false;
};

