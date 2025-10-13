#pragma once
#define NOMINMAX

#include "WinApp/WinApp.h"
#include "LogFile/LogFile.h"
#include "DirectXBase/DirectXBase.h"
#include "Func/CrushHandler/CrushHandler.h"
#include "Input/Input.h"
#include "AudioStore/AudioStore.h"
#include "Collision/Collision.h"
#include "Scene/BaseScene/BaseScene.h"
#include "Scene/SceneManager/SceneManager.h"
#include "Math/Probability/Probability.h"
#include "Math/Quaternion/Quaternion.h"
#include "Math/Vector1/Vector1.h"
#include "RecordSetting/RecordSetting.h"

// マウスボタン
enum MouseButton
{
	// 左ボタン
	kMouseButtonLeft,

	// 右ボタン
	kMouseButtonRight,

	// 中央ボタン
	kMouseButtonCenter
};

// 無限エンジン
class MugenEngine
{
public:

#pragma region メインシステム

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static MugenEngine* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// ウィンドウにメッセージを渡して応答する
	/// </summary>
	/// <returns></returns>
	bool ProcessMessage() { return winApp_->ProcessMessage(); }

	/// <summary>
	/// フレーム開始処理
	/// </summary>
	void FrameStart();

	/// <summary>
	/// フレーム終了処理
	/// </summary>
	void FrameEnd();

#pragma endregion

#pragma region キーボード入力

	/// <summary>
	/// キー入力（Press）
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns></returns>
	bool GetKeyPress(BYTE key) const { return input_->GetKeyPress(key); }

	/// <summary>
	/// キー入力（Trigger）
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns></returns>
	bool GetKeyTrigger(BYTE key) const { return input_->GetKeyTrigger(key); }

	/// <summary>
	/// キー入力（Release）
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns></returns>
	bool GetKeyRelease(BYTE key) const { return input_->GetKeyRelease(key); }

#pragma endregion

#pragma region マウス入力

	/// <summary>
	/// マウスボタン（Press）
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetMouseButtonPress(MouseButton mouseButton) const { return input_->GetMousePress(static_cast<uint32_t>(mouseButton)); };

	/// <summary>
	/// マウスボタン（Trigger）
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetMouseButtonTrigger(MouseButton mouseButton) const { return input_->GetMouseTrigger(static_cast<uint32_t>(mouseButton)); };

	/// <summary>
	/// マウスボタン（Release）
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool GetMouseButtonRelease(MouseButton mouseButton) const { return input_->GetMouseRelease(static_cast<uint32_t>(mouseButton)); };

	/// <summary>
	/// マウスの移動量のGetter
	/// </summary>
	/// <returns></returns>
	Vector2 GetMouseVelocity() const { return input_->GetMouseVelocity(); }

	/// <summary>
	/// マウスホイールが上回転しているかどうか
	/// </summary>
	/// <returns></returns>
	bool GetMouseWheelUp() const { return input_->GetMouseWheelUp(); }

	/// <summary>
	/// マウスホイールが下回転しているかどうか
	/// </summary>
	/// <returns></returns>
	bool GetMouseWheelDown()  const { return input_->GetMouseWheelDown(); }

	/// <summary>
	/// マウスホイールの回転量のGetter
	/// </summary>
	/// <returns></returns>
	float GetMouseWheelVelocity() const { return input_->GetMouseWheelVelocity(); }

#pragma endregion

#pragma region ゲームパッド入力

	/// <summary>
	/// ゲームパッドが有効かどうか
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <returns></returns>
	bool IsGamepadEnable(DWORD gamepadNumber) const { return input_->IsGamepadEnable(gamepadNumber); }

	/// <summary>
	/// ゲームパッドのボタンの入力情報（Press）
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <param name="wButtons">指定のボタン</param>
	/// <returns></returns>
	bool GetGamepadButtonPress(DWORD gamepadNumber, DWORD wButtons) const { return input_->GetGamepadButtonPress(gamepadNumber, wButtons); }

	/// <summary>
	/// ゲームパッドのボタンの入力情報（Press）
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <param name="wButtons">指定のボタン</param>
	/// <returns></returns>
	bool GetGamepadButtonTrigger(DWORD gamepadNumber, DWORD wButtons) const { return input_->GetGamepadButtonTrigger(gamepadNumber, wButtons); }

	/// <summary>
	/// ゲームパッドのボタンの入力情報（Press）
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <param name="wButtons">指定のボタン</param>
	/// <returns></returns>
	bool GetGamepadButtonRelease(DWORD gamepadNumber, DWORD wButtons) const { return input_->GetGamepadButtonRelease(gamepadNumber, wButtons); }

	/// <summary>
	/// ゲームパッドの左スティックの入力情報
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <returns></returns>
	Vector2 GetGamepadLeftStick(DWORD gamepadNumber) const { return input_->GetGamepadLeftStick(gamepadNumber); }

	/// <summary>
	/// ゲームパッドの右スティックの入力情報
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <returns></returns>
	Vector2 GetGamepadRightStick(DWORD gamepadNumber) const { return input_->GetGamepadRightStick(gamepadNumber); }

	/// <summary>
	/// ゲームパッドの左トリガーボタンの入力情報
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <returns></returns>
	float GetGamepadLeftTrigger(DWORD gamepadNumber) const { return input_->GetGamepadLeftTrigger(gamepadNumber); }

	/// <summary>
	/// ゲームパッドの右トリガーボタンの入力情報
	/// </summary>
	/// <param name="gamepadNumber">ゲームパッドの番号</param>
	/// <returns></returns>
	float GetGamepadRightTrigger(DWORD gamepadNumber) const { return input_->GetGamepadRightTrigger(gamepadNumber); }

#pragma endregion

#pragma region ゲッター

	/// <summary>
	/// スクリーン横幅のGetter
	/// </summary>
	/// <returns></returns>
	int32_t GetScreenWidth()const { return winApp_->GetClientWidth(); }

	/// <summary>
	/// スクリーン縦幅のGetter
	/// </summary>
	/// <returns></returns>
	int32_t GetScreenHeight()const { return winApp_->GetClientHeight(); }

	/// <summary>
	/// デルタタイムのGetter
	/// </summary>
	/// <returns></returns>
	float GetDeltaTime()const { return deltaTime_; }

#pragma endregion

#pragma region テクスチャ

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	TextureHandle LoadTexture(const std::string& filePath)const { return directXBase_->LoadTexture(filePath); }

	/// <summary>
	/// テクスチャの横幅を取得する
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	float GetTextureWidth(TextureHandle handle)const { return directXBase_->GetTextureWidth(handle); }

	/// <summary>
	/// テクスチャの縦幅を取得する
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	float GetTextureHeight(TextureHandle handle)const { return directXBase_->GetTextureHeight(handle); }

#pragma endregion

#pragma region モデル

	/// <summary>
	/// モデルを読み込む
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="fileName"></param>
	/// <returns></returns>
	ModelHandle LoadModel(const std::string& directory, const std::string& fileName)const { return directXBase_->LoadModel(directory, fileName); }

	/// <summary>
	/// アニメーションフラグのGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	bool IsAnimation(ModelHandle handle)const { return directXBase_->IsAnimation(handle); }

	/// <summary>
	/// アニメーション時間のGetter
	/// </summary>
	/// <param name="modelHandle"></param>
	/// <returns></returns>
	float GetAnimationDuration(ModelHandle handle)const { return directXBase_->GetAnimationDuration(handle); }

#pragma endregion

#pragma region オーディオ

	/// <summary>
	/// 音声データを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	SoundHandle LoadAudio(const std::string& filePath) const { return audioStore_->LoadAudio(filePath); }

	/// <summary>
	/// 音量の設定
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="volume"></param>
	void SetVolume(PlayHandle handle, float volume) const { audioStore_->SetVolume(handle, volume); }

	/// <summary>
	/// ピッチの設定
	/// </summary>
	/// <param name="playHandle"></param>
	/// <param name="pitch"></param>
	void SetPitch(PlayHandle handle, float pitch)const { audioStore_->SetPitch(handle, pitch); }

	/// <summary>
	/// 音声データを再生する
	/// </summary>
	/// <param name="soundHandle"></param>
	PlayHandle PlayAudio(SoundHandle handle, float volume) const { return audioStore_->PlayAudio(handle, volume); }

	/// <summary>
	/// 音声データを停止する
	/// </summary>
	/// <param name="playHandle"></param>
	void StopAudio(PlayHandle handle) const { audioStore_->StopAudio(handle); }

	/// <summary>
	/// 音楽が再生されているかどうか
	/// </summary>
	/// <param name="playHandle"></param>
	/// <returns></returns>
	bool IsAudioPlay(PlayHandle handle)const { return audioStore_->IsAudioPlay(handle); }

#pragma endregion

#pragma region パーティクル

	/// <summary>
	/// パーティクルを読み込む
	/// </summary>
	/// <param name="particleEmitter"></param>
	/// <returns></returns>
	ParticleHandle LoadParticleEmitter(BillboardParticleEmitter* particleEmitter) const { return directXBase_->LoadParticleEmitter(particleEmitter); }

	/// <summary>
	/// パーティクルを読み込む
	/// </summary>
	/// <param name="particleEmitter"></param>
	/// <returns></returns>
	ParticleHandle LoadParticleEmitter(ModelParticleEmitter* particleEmitter) const { return directXBase_->LoadParticleEmitter(particleEmitter); }

	/// <summary>
	/// 登録したパーティクルの更新処理
	/// </summary>
	/// <param name="particleHandle"></param>
	void UpdateRegistParticle(ParticleHandle particleHandle) const { directXBase_->UpdateRegistParticle(particleHandle); }

	/// <summary>
	/// モデルハンドルのSetter
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <param name="modelHandle"></param>
	void SetParticleModelHandle(ParticleHandle particleHandle, ModelHandle modelHandle) const { directXBase_->SetParticleModelHandle(particleHandle, modelHandle); }

	/// <summary>
	/// テクスチャハンドルのSetter
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <param name="textureHandle"></param>
	void SetParticleTextureHandle(ParticleHandle particleHandle, TextureHandle textureHandle) const { directXBase_->SetParticleTextureHandle(particleHandle, textureHandle); }

	/// <summary>
	/// ビルボードパーティクルを描画する
	/// </summary>
	/// <param name="particleHandle"></param>
	/// <param name="camera"></param>
	void DrawBillboardParticle(ParticleHandle particleHandle, const Camera3D* camera) const { directXBase_->DrawBillboardParticle(particleHandle, camera); }

	/// <summary>
	/// モデルパーティクルを描画する
	/// </summary>
	/// <param name=""></param>
	/// <param name="camera"></param>
	void DrawModelParticle(ParticleHandle particleHandle, const Camera3D* camera) const { directXBase_->DrawModelParticle(particleHandle, camera); }

#pragma endregion

#pragma region 衝突判定

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="s1">球</param>
	/// <param name="s2">球</param>
	/// <returns></returns>
	bool IsCollision(const Sphere& s1, const Sphere& s2)const { return collision_->IsCollision(s1, s2); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb1">AABB</param>
	/// <param name="aabb2">AABB</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb1, const AABB& aabb2)const { return collision_->IsCollision(aabb1, aabb2); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb1, const OBB& obb2)const { return collision_->IsCollision(obb1, obb2); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="sphere">球</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Sphere& sphere)const { return collision_->IsCollision(aabb, sphere); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="aabb">AABB</param>
	/// <returns></returns>
	bool IsCollision(const Sphere& sphere, const AABB& aabb)const { return collision_->IsCollision(aabb, sphere); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="sphere">球</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Sphere& sphere)const { return collision_->IsCollision(obb, sphere); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="obb">OBB</param>
	/// <returns></returns>
	bool IsCollision(const Sphere& sphere, const OBB& obb)const { return collision_->IsCollision(obb, sphere); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="obb">OBB</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const OBB& obb)const { return collision_->IsCollision(aabb, obb); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="aabb">AABB</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const AABB& aabb)const { return collision_->IsCollision(aabb, obb); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <returns></returns>
	bool IsCollision(const Sphere& sphere, const Plane& plane)const { return collision_->IsCollision(sphere, plane); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="sphere">球</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Sphere& sphere)const { return collision_->IsCollision(sphere, plane); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Line& line)const { return collision_->IsCollision(plane, line); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="line">直線</param>
	/// <param name="plane">平面</param>
	/// <returns></returns>
	bool IsCollision(const Line& line, const Plane& plane)const { return collision_->IsCollision(plane, line); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Ray& ray)const { return collision_->IsCollision(plane, ray); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="ray">半直線</param>
	/// <param name="plane">平面</param>
	/// <returns></returns>
	bool IsCollision(const Ray& ray, const Plane& plane)const { return collision_->IsCollision(plane, ray); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Segment& segment)const { return collision_->IsCollision(plane, segment); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="segment">線分</param>
	/// <param name="plane">平面</param>
	/// <returns></returns>
	bool IsCollision(const Segment& segment, const Plane& plane)const { return collision_->IsCollision(plane, segment); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="triangle">三角形</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const Triangle& triangle, const Line& line)const { return collision_->IsCollision(triangle, line); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="line">直線</param>
	/// <param name="triangle">三角形</param>
	/// <returns></returns>
	bool IsCollision(const Line& line, const Triangle& triangle)const { return collision_->IsCollision(triangle, line); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="triangle">三角形</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const Triangle& triangle, const Ray& ray)const { return collision_->IsCollision(triangle, ray); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="ray">半直線</param>
	/// <param name="triangle">三角形</param>
	/// <returns></returns>
	bool IsCollision(const Ray& ray, const Triangle& triangle)const { return collision_->IsCollision(triangle, ray); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="triangle">三角形</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const Triangle& triangle, const Segment& segment)const { return collision_->IsCollision(triangle, segment); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="segment">線分</param>
	/// <param name="triangle">三角形</param>
	/// <returns></returns>
	bool IsCollision(const Segment& segment, const Triangle& triangle)const { return collision_->IsCollision(triangle, segment); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Line& line)const { return collision_->IsCollision(aabb, line); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="line">直線</param>
	/// <param name="aabb">AABB</param>
	/// <returns></returns>
	bool IsCollision(const Line& line, const AABB& aabb)const { return collision_->IsCollision(aabb, line); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Ray& ray)const { return collision_->IsCollision(aabb, ray); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="ray">半直線</param>
	/// <param name="aabb">AABB</param>
	/// <returns></returns>
	bool IsCollision(const Ray& ray, const AABB& aabb)const { return collision_->IsCollision(aabb, ray); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Segment& segment)const { return collision_->IsCollision(aabb, segment); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="segment">線分</param>
	/// <param name="aabb">AABB</param>
	/// <returns></returns>
	bool IsCollision(const Segment& segment, const AABB& aabb)const { return collision_->IsCollision(aabb, segment); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Line& line)const { return collision_->IsCollision(obb, line); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="line">直線</param>
	/// <param name="obb">OBB</param>
	/// <returns></returns>
	bool IsCollision(const Line& line, const OBB& obb)const { return collision_->IsCollision(obb, line); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Ray& ray)const { return collision_->IsCollision(obb, ray); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="ray">半直線</param>
	/// <param name="obb">OBB</param>
	/// <returns></returns>
	bool IsCollision(const Ray& ray, const OBB& obb)const { return collision_->IsCollision(obb, ray); }



	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Segment& segment)const { return collision_->IsCollision(obb, segment); }

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="segment">線分</param>
	/// <param name="obb">OBB</param>
	/// <returns></returns>
	bool IsCollision(const Segment& segment, const OBB& obb)const { return collision_->IsCollision(obb, segment); }


#pragma endregion

#pragma region 描画処理

	/// <summary>
	/// モデルを描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="modelHandle"></param>
	/// <param name="color"></param>
	/// <param name="enableLighting"></param>
	/// <param name="enableHalfLanbert"></param>
	void DrawModel(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, ModelHandle modelHandle,
		const Material* material, float animationTimer) const
	{
		directXBase_->DrawModel(worldTransform, uvTransform, camera, modelHandle, material, animationTimer);
	}

	/// <summary>
	/// スプライトを描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	void DrawSprite(const WorldTransform2D* worldTransform, const Vector2& anchor, const Vector2& textureLeftTop, const Vector2& textureSize,
		const UVTransform* uvTransform, const Camera2D* camera, TextureHandle textureHandle, const Vector4& color, bool isFlipX, bool isFlipY)const;

	/// <summary>
	/// 平面を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="material"></param>
	void DrawPlane(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, TextureHandle textureHandle,
		const Material* material) const
	{
		directXBase_->DrawPlane(worldTransform, uvTransform, camera, textureHandle, material);
	}

	/// <summary>
	/// UV球を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="color"></param>
	/// <param name="enableLighting"></param>
	/// <param name="enableHalfLanbert"></param>
	/// <param name="segment"></param>
	/// <param name="ring"></param>
	void DrawUVSphere(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, TextureHandle textureHandle,
		const Material* material,int32_t segment, int32_t ring) const
	{
		directXBase_->DrawUVSphere(worldTransform, uvTransform, camera, textureHandle, material, segment, ring);
	}

	/// <summary>
	/// 立方体を描画する
	/// </summary>
	/// <param name="worldTransform"></param>
	/// <param name="uvTransform"></param>
	/// <param name="camera"></param>
	/// <param name="textureHandle"></param>
	/// <param name="color"></param>
	/// <param name="enableLighting"></param>
	/// <param name="enableHalfLanbert"></param>
	void DrawCube(const WorldTransform3D* worldTransform, const UVTransform* uvTransform, const Camera3D* camera, TextureHandle textureHandle,
		const Material* material) const
	{
		directXBase_->DrawCube(worldTransform, uvTransform, camera, textureHandle, material);
	}

#pragma endregion

#pragma region ブレンドモード

	/// <summary>
	/// プリミティブのブレンドモードを設定する
	/// </summary>
	/// <param name="blendMode"></param>
	void SetBlendModePrimitive(BlendMode blendMode)const { directXBase_->SetBlendModePrimitive(blendMode); }

#pragma endregion

#pragma region 調整記録

	/// <summary>
	/// 設定したい値を設定する
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="groupName"></param>
	/// <param name="key"></param>
	/// <param name="value"></param>
	template<typename T>
	void SetSettingValue(const std::string& groupName, const std::string& key, T* value)const { recordSetting_->SetValue(groupName, key, value); }

	/// <summary>
	/// 登録した調整項目の値に、ファイルの値を反映させる
	/// </summary>
	/// <param name="groupName"></param>
	void RegistGroupDataReflection(const std::string& groupName)const { recordSetting_->RegistGroupDataReflection(groupName); }

#pragma endregion


private:

	// シングルトン
	MugenEngine() = default;
	~MugenEngine() = default;
	MugenEngine(MugenEngine&) = delete;
	MugenEngine& operator=(MugenEngine&) = delete;

	// インスタンス
	static MugenEngine* instance_;



	// クライアント領域横幅
	const int32_t* kClientWidth_ = nullptr;

	// クライアント領域縦幅
	const int32_t* kClientHeight_ = nullptr;


	// ログファイル
	std::unique_ptr<LogFile> logFile_ = nullptr;

	// ウィンドウズアプリケーション
	std::unique_ptr<WinApp> winApp_ = nullptr;
	
	// DirectXのベース
	std::unique_ptr<DirectXBase> directXBase_ = nullptr;

	// 入力
	std::unique_ptr<Input> input_ = nullptr;

	// オーディオ格納場所
	AudioStore* audioStore_ = nullptr;

	// 衝突判定
	std::unique_ptr<Collision> collision_ = nullptr;

	// 設定記録
	RecordSetting* recordSetting_ = nullptr;

	// シーンマネージャー
	SceneManager* sceneManager_ = nullptr;


	// デルタタイム
	float deltaTime_ = 1.0f / 60.0f;
};

