#include "BaseParticleData.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void BaseParticleData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap,
	uint32_t numMaxParticle, ParticleHandle particleHandle)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(directXHeap);

	// 引数を受け取る
	device_ = device;
	commandList_ = commandList;
	directXHeap_ = directXHeap;
	numMaxParticle_ = numMaxParticle;
	particleHandle_ = particleHandle;

	// インスタンスを取得する
	engine_ = MugenEngine::GetInstance();

	// 座標変換インスタンシングリソースの生成と初期化
	transformationResource_ = std::make_unique<TransformationResourceDataInstancing>();
	transformationResource_->Initialize(device_, commandList_,directXHeap_ , numMaxParticle_);
}


/// <summary>
/// 値のポインタをセットする
/// </summary>
/// <param name="position"></param>
/// <param name="emitNum"></param>
/// <param name="emitTime"></param>
void BaseParticleData::SetValueP(Vector3* position, uint32_t* emitNum, float* emitTime, std::string* name)
{
	// nullptrチェック
	assert(position);
	assert(emitNum);
	assert(emitTime);
	assert(name);

	// 引数を受け取る
	position_ = position;
	emitNum_ = emitNum;
	emitTime_ = emitTime;
	name_ = name;

	RecordSetting::GetInstance()->SetValue(*name_, "position", position_);
	RecordSetting::GetInstance()->RegistGroupDataReflection(*name_);
}


/// <summary>
/// 更新処理
/// </summary>
void BaseParticleData::Update()
{
	// タイマーを進める
	emitTimer_ += engine_->GetDeltaTime();

	// タイマーが越えたら放出する
	if (emitTimer_ >= *emitTime_)
	{
		// 放出数に合わせる
		for (uint32_t i = 0; i < *emitNum_; ++i)
		{
			// 最大数を越えないようにする
			if (particles_.size() >= numMaxParticle_)
				break;

			// パーティクルの生成と初期化
			std::unique_ptr<ParticleInstance> particle = std::make_unique<ParticleInstance>();
			particle->Initialize(*position_, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.5f);
			particles_.push_back(std::move(particle));
		}

		emitTimer_ = 0.0f;
	}


	int numEmitParticle = 0;

	// パーティクルの更新処理
	for (std::unique_ptr<ParticleInstance>& particle : particles_)
	{
		particle->Update();
	}

	// 終了したパーティクルを削除する
	particles_.remove_if([](std::unique_ptr<ParticleInstance>& particle)
		{
			if (particle->IsFinished())
			{
				particle = nullptr;
				return true;
			}
			return false;
		}
	);
}


/// <summary>
/// コマンドリストに登録する
/// </summary>
/// <param name="transformationRootParameterIndex"></param>
void BaseParticleData::Register(UINT transformationRootParameterIndex)
{
	// 座標変換インスタンシングの設定
	transformationResource_->Register(transformationRootParameterIndex);
}