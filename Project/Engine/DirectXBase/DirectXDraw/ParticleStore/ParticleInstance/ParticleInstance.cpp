#include "ParticleInstance.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="position"></param>
void ParticleInstance::Initialize(const Vector3& position, const Vector3& rotation , const Vector3& scale, float emitTime)
{
	// インスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// トランスフォームの値
	transform.translate = position;
	transform.rotate = rotation;
	transform.scale = scale;

	sizeStart_ = scale;

	// 放出時間
	emitTime_ = emitTime;
}

/// <summary>
/// 更新処理
/// </summary>
void ParticleInstance::Update()
{
	// タイマーを進める
	emitTimer_ += engine_->GetDeltaTime();

	// 時間を越えらたら終了する
	if (emitTimer_ >= emitTime_)
	{
		isFinished_ = true;
		return;
	}

	// 補間
	float t = emitTimer_ / emitTime_;
	
	float speed = Lerp(speedStart_, speedFinal_, t);
	transform.scale = Lerp(sizeStart_, sizeFinal_, t);
	


	// 加速度を加算する
	gravitySpeed_ += gravityAcceleration_ * engine_->GetDeltaTime();

	// 重力
	Vector3 gravity = gravityDirection_ * gravitySpeed_ * engine_->GetDeltaTime();

	// 速度ベクトル
	Vector3 speedVector = (direction_ * speed) * engine_->GetDeltaTime();

		// 移動させる
	transform.translate += speedVector + gravity;
}