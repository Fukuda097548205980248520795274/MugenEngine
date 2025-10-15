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
	particleResourcesInstancing_ = std::make_unique<ParticleDataInstancing>();
	particleResourcesInstancing_->Initialize(device_, commandList_,directXHeap_ , numMaxParticle_);


	// メモリを割り当てる
	position_ = (Vector3*)malloc(sizeof(Vector3));
	perEmission_ = (uint32_t*)malloc(sizeof(uint32_t));

	emitTime_ = (float*)malloc(sizeof(float));
	emitRange_ = (Vector3*)malloc(sizeof(Vector3));
	enableSphere_ = (RANGETYPE*)malloc(sizeof(RANGETYPE));

	sizeRange_ = (Vector2*)malloc(sizeof(Vector2));
	sizeFinal_ = (float*)malloc(sizeof(float));

	speedRange_ = (Vector2*)malloc(sizeof(Vector2));
	speedFinal_ = (float*)malloc(sizeof(float));

	releasedTimeRange_ = (Vector2*)malloc(sizeof(Vector2));

	colorStart_ = (Vector4*)malloc(sizeof(Vector4));
	colorFinal_ = (Vector4*)malloc(sizeof(Vector4));

	gravityDirection_ = (Vector3*)malloc(sizeof(Vector3));
	gravityAcceleration_ = (float*)malloc(sizeof(float));


	// 初期値を割り当てる
	*position_ = Vector3(0.0f, 0.0f, 0.0f);
	*perEmission_ = 1;

	*emitTime_ = 0.1f;
	*emitRange_ = Vector3(0.0f, 0.0f, 0.0f);
	*enableSphere_ = RANGETYPE::AABB;

	*sizeRange_ = Vector2(1.0f, 1.0f);
	*sizeFinal_ = 0.0f;

	*speedRange_ = Vector2(8.0f, 8.0f);
	*speedFinal_ = 0.0f;

	*releasedTimeRange_ = Vector2(1.0f, 1.0f);

	*colorStart_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	*colorFinal_ = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	*gravityDirection_ = Vector3(0.0f, -1.0f, 0.0f);
	*gravityAcceleration_ = 0.0f;

	name_ = name;


	// 調整項目
	RecordSetting* recordSetting = RecordSetting::GetInstance();
	recordSetting->SetValue(*name_, "emit_position", position_);
	recordSetting->SetValue(*name_, "emit_perEmission", perEmission_);
	recordSetting->SetValue(*name_, "emit_Time", emitTime_);
	recordSetting->SetValue(*name_, "emit_Range", emitRange_);
	recordSetting->SetValue(*name_, "emit_Range_Type", enableSphere_);
	recordSetting->SetValue(*name_, "size_Range", sizeRange_);
	recordSetting->SetValue(*name_, "size_Final", sizeFinal_);
	recordSetting->SetValue(*name_, "speed_Range", speedRange_);
	recordSetting->SetValue(*name_, "speed_Final", speedFinal_);
	recordSetting->SetValue(*name_, "releasedTimeRange", releasedTimeRange_);
	recordSetting->SetValue(*name_, "color_Start", colorStart_);
	recordSetting->SetValue(*name_, "color_Final", colorFinal_);
	recordSetting->SetValue(*name_, "gravity_Direction", gravityDirection_);
	recordSetting->SetValue(*name_, "gravity_Acceleration", gravityAcceleration_);
	recordSetting->RegistGroupDataReflection(*name_);
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
		for (int32_t i = 0; i < *perEmission_; ++i)
		{
			// 最大数を越えないようにする
			if (particles_.size() >= numMaxParticle_)
				break;

			// サイズ
			float size = GetRandomRange(sizeRange_->x, sizeRange_->y);
			Vector3 scale = Vector3(size, size, size);

			// 速度
			float speed = GetRandomRange(speedRange_->x, speedRange_->y);

			// 放出される時間
			float releasedTime = GetRandomRange(releasedTimeRange_->x, releasedTimeRange_->y);


			// 発生範囲のワールド座標
			Vector3 emitPosition = Vector3(0.0f, 0.0f, 0.0f);

			if (*enableSphere_ == RANGETYPE::SPHERE)
			{
				float length = Length(*emitRange_);
				Vector3 vector = Normalize(Vector3(GetRandomRange(-2.0f, 2.0f), GetRandomRange(-2.0f, 2.0f), GetRandomRange(-2.0f, 2.0f)));
				emitPosition = vector * GetRandomRange(0.0f, length);
			}
			else if(*enableSphere_ == RANGETYPE::AABB)
			{
				std::pair<float, float> rangeX;
				rangeX.first = position_->x - emitRange_->x;
				rangeX.second = position_->x + emitRange_->x;

				std::pair<float, float> rangeY;
				rangeY.first = position_->y - emitRange_->y;
				rangeY.second = position_->y + emitRange_->y;

				std::pair<float, float> rangeZ;
				rangeZ.first = position_->z - emitRange_->z;
				rangeZ.second = position_->z + emitRange_->z;

				emitPosition =
					Vector3(GetRandomRange(rangeX.first, rangeX.second), GetRandomRange(rangeY.first, rangeY.second), GetRandomRange(rangeZ.first, rangeZ.second));
			}


			// パーティクルの生成と初期化
			std::unique_ptr<ParticleInstance> particle = std::make_unique<ParticleInstance>();
			particle->Initialize(emitPosition, Vector3(0.0f, 0.0f, 0.0f), scale, releasedTime,*colorStart_);
			particle->SetDirection(Normalize(Vector3(GetRandomRange(-2.0f, 2.0f), GetRandomRange(-2.0f, 2.0f), GetRandomRange(-2.0f, 2.0f))));

			particle->SetSizeFinal(Vector3(*sizeFinal_, *sizeFinal_, *sizeFinal_));
			
			particle->SpeedStart(speed);
			particle->SpeedFinal(*speedFinal_);

			particle->SetColorFinal(*colorFinal_);

			particle->SetGravityDirection(*gravityDirection_);
			particle->SetGravityAcceleration(*gravityAcceleration_);

			// リストに登録する
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
	particleResourcesInstancing_->Register(transformationRootParameterIndex);
}