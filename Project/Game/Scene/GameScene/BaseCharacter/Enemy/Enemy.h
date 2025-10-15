#pragma once
#include "../BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera3d"></param>
	/// <param name="startPosition"></param>
	void Initialize(const Camera3D* camera3d, const Vector3& startPosition) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;


private:

	// モデル
	std::unique_ptr<MeshModel> model_ = nullptr;
};

