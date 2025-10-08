#pragma once
#include "../BaseCharacter.h"

class Player : public BaseCharacter
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera3d"></param>
	/// <param name="startPosition"></param>
	void Initialize(const MugenEngine* engine, const Camera3D* camera3d, const Vector3& startPosition) override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;


private:

	// 移動操作　キー
	std::unique_ptr<InputMoveKey> inputMoveKey_ = nullptr;

	// 移動操作　ゲームパッド
	std::unique_ptr<InputMoveGamepad> inputMoveGamepad_ = nullptr;


	// 移動ロジック
	std::unique_ptr<LogicMove> logicMove_ = nullptr;

	// 移動速度ロジック
	std::unique_ptr<LogicMoveSpeed> logicMoveSpeed_ = nullptr;


	// モデル
	std::unique_ptr<MeshModel> model_ = nullptr;
};

