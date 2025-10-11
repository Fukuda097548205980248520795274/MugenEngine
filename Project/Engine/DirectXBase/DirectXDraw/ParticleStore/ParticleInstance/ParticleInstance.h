#pragma once
#include "Math/Vector3/Vector3.h"
#include "Math/Matrix4x4/Matrix4x4.h"
#include "../../BaseMesh/MeshOptions/Transform/Transform.h"

// 前方宣言
class MugenEngine;

class ParticleInstance
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position"></param>
	void Initialize(const Vector3& position, const Vector3& rotation, const Vector3& scale, float emitTime);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 終了フラグのGetter
	/// </summary>
	/// <returns></returns>
	bool IsFinished()const { return isFinished_; }

	/// <summary>
	/// 平行移動のGetter
	/// </summary>
	/// <returns></returns>
	Vector3 GetTranslate()const { return transform.translate; }

	/// <summary>
	/// 拡縮のGetter
	/// </summary>
	/// <returns></returns>
	Vector3 GetScale()const { return transform.scale; }

	/// <summary>
	/// 回転のGetter
	/// </summary>
	/// <returns></returns>
	Vector3 GetRotate()const { return transform.rotate; }


private:

	// エンジン
	class MugenEngine* engine_ = nullptr;

	// 放出タイマー
	float emitTimer_ = 0.0f;

	// 終了フラグ
	bool isFinished_ = false;


	// トランスフォーム
	EulerTransform3D transform;

	// 放出時間
	float emitTime_ = 0.0f;
};

