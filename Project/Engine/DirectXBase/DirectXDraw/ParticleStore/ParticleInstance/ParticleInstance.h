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


	/// <summary>
	/// 方向のSetter
	/// </summary>
	/// <param name="direction"></param>
	void SetDirection(const Vector3& direction) { direction_ = direction; }


	/// <summary>
	/// 最終的な大きさ
	/// </summary>
	/// <param name="scale"></param>
	void SetSizeFinal(const Vector3& scale) { sizeFinal_ = scale; }


	/// <summary>
	/// 最初の速度のSetter
	/// </summary>
	/// <param name="speedStart"></param>
	void SpeedStart(float speedStart) { speedStart_ = speedStart; }

	/// <summary>
	/// 最後の速度のSetter
	/// </summary>
	/// <param name="speedFinal"></param>
	void SpeedFinal(float speedFinal) { speedFinal_ = speedFinal; }


	/// <summary>
	/// 重力方向のSetter
	/// </summary>
	/// <param name="directionGraivity"></param>
	void SetGravityDirection(const Vector3& directionGraivity) { gravityDirection_ = Normalize(directionGraivity); }

	/// <summary>
	/// 周力加速度のSetter
	/// </summary>
	/// <param name="gravityAcceleration"></param>
	void SetGravityAcceleration(float gravityAcceleration) { gravityAcceleration_ = gravityAcceleration; }


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


	// 最初のサイズ
	Vector3 sizeStart_ = Vector3(0.0f, 0.0f, 0.0f);

	// 最終的なサイズ
	Vector3 sizeFinal_ = Vector3(0.0f, 0.0f, 0.0f);


	// 方向
	Vector3 direction_ = Vector3(0.0f, 0.0f, 0.0f);

	// 最初の速度
	float speedStart_ = 0.0f;

	// 最終的な速度
	float speedFinal_ = 0.0f;




	// 重力方向
	Vector3 gravityDirection_ = Vector3(0.0f, -1.0f, 0.0f);

	// 重力加速度
	float gravityAcceleration_ = 9.8f;

	// 重力速度
	float gravitySpeed_ = 0.0f;
};

