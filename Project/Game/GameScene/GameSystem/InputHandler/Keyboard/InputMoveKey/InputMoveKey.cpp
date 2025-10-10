#include "InputMoveKey.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
/// <param name="front"></param>
/// <param name="left"></param>
/// <param name="back"></param>
/// <param name="right"></param>
void InputMoveKey::Initialize(const MugenEngine* engine, BYTE front, BYTE left, BYTE back, BYTE right)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
	front_ = front;
	left_ = left;
	back_ = back;
	right_ = right;
}

/// <summary>
/// 押したキーに合わせて方向ベクトルを求める
/// </summary>
/// <returns></returns>
Vector3 InputMoveKey::GetMoveDirection()
{
	// 方向ベクトル
	Vector3 direction = Vector3(0.0f, 0.0f, 0.0f);

	// 奥移動
	if (IsFront())
		direction.z = 1.0f;

	// 左移動
	if (IsLeft())
		direction.x = -1.0f;

	// 手前移動
	if (IsBack())
		direction.z = -1.0f;

	// 右移動
	if (IsRight())
		direction.x = 1.0f;

	// 正規化する
	return Normalize(direction);
}