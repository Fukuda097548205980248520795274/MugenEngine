#pragma once
#include "MugenEngine.h"

#include "GameScene/GameSystem/InputHandler/InputMoveGamepad/InputMoveGamepad.h"
#include "GameScene/GameSystem/InputHandler/InputMoveKey/InputMoveKey.h"
#include "GameScene/GameSystem/MovementLogic/LogicMove/LogicMove.h"
#include "GameScene/GameSystem/MovementLogic/LogicMoveSpeed/LogicMoveSpeed.h"

class BaseCharacter
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	/// <param name="camera3d"></param>
	/// <param name="startPosition"></param>
	virtual void Initialize(const MugenEngine* engine, const Camera3D* camera3d, const Vector3& startPosition);

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;


protected:

	// エンジン
	const MugenEngine* engine_ = nullptr;

	// 3Dカメラ
	const Camera3D* camera3d_ = nullptr;


	// ワールドトランスフォーム
	std::unique_ptr<WorldTransform3D> worldTransform_ = nullptr;
};

