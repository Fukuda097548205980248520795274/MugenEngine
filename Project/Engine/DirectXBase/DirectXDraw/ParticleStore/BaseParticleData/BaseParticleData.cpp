#include "BaseParticleData.h"
#include "MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
void BaseParticleData::Initialize(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, DirectXHeap* directXHeap,
	uint32_t numMaxParticle, ParticleHandle particleHandle, std::string* name)
{
	// nullptrチェック
	assert(device);
	assert(commandList);
	assert(directXHeap);
	assert(name);

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


	// メモリを割り当てる
	position_ = (Vector3*)malloc(sizeof(Vector3));
	perEmission_ = (int32_t*)malloc(sizeof(int32_t));
	emitTime_ = (float*)malloc(sizeof(float));
	emitRange_ = (Vector3*)malloc(sizeof(Vector3));

	// 初期値を割り当てる
	*position_ = Vector3(0.0f, 0.0f, 0.0f);
	*perEmission_ = 1;
	*emitTime_ = 0.1f;
	*emitRange_ = Vector3(0.0f, 0.0f, 0.0f);

	name_ = name;


	RecordSetting* recordSetting = RecordSetting::GetInstance();
	recordSetting->SetValue(*name_, "position", position_);
	recordSetting->SetValue(*name_, "perEmission", perEmission_);
	recordSetting->SetValue(*name_, "emitTime", emitTime_);
	recordSetting->SetValue(*name_, "emitRange", emitRange_);
	recordSetting->RegistGroupDataReflection(*name_);
}


/// <summary>
/// 更新処理
/// </summary>
void BaseParticleData::Update()
{
	// タイマーを進める
	emitTimer_ += engine_->GetDeltaTime();


	// 発生範囲のワールド座標
	std::pair<float, float> rangeX;
	rangeX.first = position_->x - emitRange_->x;
	rangeX.second = position_->x + emitRange_->x;

	std::pair<float, float> rangeY;
	rangeY.first = position_->y - emitRange_->y;
	rangeY.second = position_->y + emitRange_->y;

	std::pair<float, float> rangeZ;
	rangeZ.first = position_->z - emitRange_->z;
	rangeZ.second = position_->z + emitRange_->z;


	// タイマーが越えたら放出する
	if (emitTimer_ >= *emitTime_)
	{
		// 放出数に合わせる
		for (int32_t i = 0; i < *perEmission_; ++i)
		{
			// 最大数を越えないようにする
			if (particles_.size() >= numMaxParticle_)
				break;

			// パーティクルの生成と初期化
			std::unique_ptr<ParticleInstance> particle = std::make_unique<ParticleInstance>();
			particle->Initialize(Vector3(GetRandomRange(rangeX.first, rangeX.second), GetRandomRange(rangeY.first, rangeY.second), GetRandomRange(rangeZ.first, rangeZ.second)),
				Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), 0.5f);
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