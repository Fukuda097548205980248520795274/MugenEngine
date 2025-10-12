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
}