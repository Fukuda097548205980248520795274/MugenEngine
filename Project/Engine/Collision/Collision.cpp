#include "Collision.h"
#include "../MugenEngine.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="engine"></param>
void Collision::Initialize(const MugenEngine* engine)
{
	// nullptrチェック
	assert(engine);

	// 引数を受け取る
	engine_ = engine;
}



/// <summary>
/// 衝突判定
/// </summary>
/// <param name="s1">球</param>
/// <param name="s2">球</param>
bool Collision::IsCollision(const Sphere& s1, const Sphere& s2)
{
	if (s1.radius + s2.radius >=
		Length(s2.center - s1.center))
	{
		return true;
	}

	return false;
}



/// <summary>
/// 衝突判定
/// </summary>
/// <param name="aabb1">AABB</param>
/// <param name="aabb2">AABB</param>
/// <returns></returns>
bool Collision::IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if (aabb1.max.x >= aabb2.min.x &&
		aabb2.max.x >= aabb1.min.x)
	{
		if (aabb1.max.y >= aabb2.min.y &&
			aabb2.max.y >= aabb1.min.y)
		{
			if (aabb1.max.z >= aabb2.min.z &&
				aabb2.max.z >= aabb1.min.z)
			{
				return true;
			}
		}
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="obb1">OBB</param>
/// <param name="obb2">OBB</param>
/// <returns></returns>
bool Collision::IsCollision(const OBB& obb1, const OBB& obb2)
{
	/*-----------------------
		ワールド座標を求める
	-----------------------*/

	/*   OBB1   */

	// ワールド行列
	Matrix4x4 obbWorld1;

	obbWorld1.m[0][0] = obb1.oriented[0].x;
	obbWorld1.m[0][1] = obb1.oriented[0].y;
	obbWorld1.m[0][2] = obb1.oriented[0].z;
	obbWorld1.m[0][3] = 0.0f;

	obbWorld1.m[1][0] = obb1.oriented[1].x;
	obbWorld1.m[1][1] = obb1.oriented[1].y;
	obbWorld1.m[1][2] = obb1.oriented[1].z;
	obbWorld1.m[1][3] = 0.0f;

	obbWorld1.m[2][0] = obb1.oriented[2].x;
	obbWorld1.m[2][1] = obb1.oriented[2].y;
	obbWorld1.m[2][2] = obb1.oriented[2].z;
	obbWorld1.m[2][3] = 0.0f;

	obbWorld1.m[3][0] = obb1.center.x;
	obbWorld1.m[3][1] = obb1.center.y;
	obbWorld1.m[3][2] = obb1.center.z;
	obbWorld1.m[3][3] = 1.0f;


	// ローカル座標
	Vector3 local1[8];
	local1[0] = { -obb1.size.x , -obb1.size.y , -obb1.size.z };
	local1[1] = { obb1.size.x , -obb1.size.y , -obb1.size.z };
	local1[2] = { -obb1.size.x , -obb1.size.y , obb1.size.z };
	local1[3] = { obb1.size.x , -obb1.size.y , obb1.size.z };
	local1[4] = { -obb1.size.x , obb1.size.y , -obb1.size.z };
	local1[5] = { obb1.size.x , obb1.size.y , -obb1.size.z };
	local1[6] = { -obb1.size.x , obb1.size.y , obb1.size.z };
	local1[7] = { obb1.size.x , obb1.size.y , obb1.size.z };


	// ワールド座標
	Vector3 world1[8];
	for (uint32_t i = 0; i < 8; i++)
	{
		world1[i] = Transform(local1[i], obbWorld1);
	}


	/*   OBB2   */

	// ワールド行列
	Matrix4x4 obbWorld2;

	obbWorld2.m[0][0] = obb2.oriented[0].x;
	obbWorld2.m[0][1] = obb2.oriented[0].y;
	obbWorld2.m[0][2] = obb2.oriented[0].z;
	obbWorld2.m[0][3] = 0.0f;

	obbWorld2.m[1][0] = obb2.oriented[1].x;
	obbWorld2.m[1][1] = obb2.oriented[1].y;
	obbWorld2.m[1][2] = obb2.oriented[1].z;
	obbWorld2.m[1][3] = 0.0f;

	obbWorld2.m[2][0] = obb2.oriented[2].x;
	obbWorld2.m[2][1] = obb2.oriented[2].y;
	obbWorld2.m[2][2] = obb2.oriented[2].z;
	obbWorld2.m[2][3] = 0.0f;

	obbWorld2.m[3][0] = obb2.center.x;
	obbWorld2.m[3][1] = obb2.center.y;
	obbWorld2.m[3][2] = obb2.center.z;
	obbWorld2.m[3][3] = 1.0f;


	// ローカル座標
	Vector3 local2[8];
	local2[0] = { -obb2.size.x , -obb2.size.y , -obb2.size.z };
	local2[1] = { obb2.size.x , -obb2.size.y , -obb2.size.z };
	local2[2] = { -obb2.size.x , -obb2.size.y , obb2.size.z };
	local2[3] = { obb2.size.x , -obb2.size.y , obb2.size.z };
	local2[4] = { -obb2.size.x , obb2.size.y , -obb2.size.z };
	local2[5] = { obb2.size.x , obb2.size.y , -obb2.size.z };
	local2[6] = { -obb2.size.x , obb2.size.y , obb2.size.z };
	local2[7] = { obb2.size.x , obb2.size.y , obb2.size.z };


	// ワールド座標
	Vector3 world2[8];
	for (uint32_t i = 0; i < 8; i++)
	{
		world2[i] = Transform(local2[i], obbWorld2);
	}


	/*------------
		分離軸
	------------*/

	/*   面法線 OBB1 X   */

	Vector3 normal = obb1.oriented[0];

	float min1 = Dot(world1[0], normal);
	float max1 = Dot(world1[0], normal);

	float min2 = Dot(world2[0], normal);
	float max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	float sumSpan = (max1 - min1) + (max2 - min2);
	float longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB1 Y   */

	normal = obb1.oriented[1];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB1 Z   */

	normal = obb1.oriented[2];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB2 X   */

	normal = obb2.oriented[0];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB2 Y   */

	normal = obb2.oriented[1];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB2 Z   */

	normal = obb2.oriented[2];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : X , OBB2 : X   */

	normal = Normalize(Cross(obb1.oriented[0], obb2.oriented[0]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : X , OBB2 : Y   */

	normal = Normalize(Cross(obb1.oriented[0], obb2.oriented[1]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : X , OBB2 : Z   */

	normal = Normalize(Cross(obb1.oriented[0], obb2.oriented[2]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : Y , OBB2 : X   */

	normal = Normalize(Cross(obb1.oriented[1], obb2.oriented[0]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : Y , OBB2 : Y   */

	normal = Normalize(Cross(obb1.oriented[1], obb2.oriented[1]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : Y , OBB2 : Z   */

	normal = Normalize(Cross(obb1.oriented[1], obb2.oriented[2]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : Z , OBB2 : X   */

	normal = Normalize(Cross(obb1.oriented[2], obb2.oriented[0]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : Z , OBB2 : Y   */

	normal = Normalize(Cross(obb1.oriented[2], obb2.oriented[1]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 OBB1 : Z , OBB2 : Z   */

	normal = Normalize(Cross(obb1.oriented[2], obb2.oriented[2]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	return true;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="obb">OBB</param>
/// <returns></returns>
bool Collision::IsCollision(const AABB& aabb, const OBB& obb)
{
	/*-----------------------
		ワールド座標を求める
	-----------------------*/

	/*   AABB   */

	// ワールド行列
	Matrix4x4 aabbWorld;

	aabbWorld.m[0][0] = 1.0f;
	aabbWorld.m[0][1] = 0.0f;
	aabbWorld.m[0][2] = 0.0f;
	aabbWorld.m[0][3] = 0.0f;

	aabbWorld.m[1][0] = 0.0f;
	aabbWorld.m[1][1] = 1.0f;
	aabbWorld.m[1][2] = 0.0f;
	aabbWorld.m[1][3] = 0.0f;

	aabbWorld.m[2][0] = 0.0f;
	aabbWorld.m[2][1] = 0.0f;
	aabbWorld.m[2][2] = 1.0f;
	aabbWorld.m[2][3] = 0.0f;

	aabbWorld.m[3][0] = ((aabb.max.x - aabb.min.x) / 2.0f) + aabb.min.x;
	aabbWorld.m[3][1] = ((aabb.max.y - aabb.min.y) / 2.0f) + aabb.min.y;
	aabbWorld.m[3][2] = ((aabb.max.z - aabb.min.z) / 2.0f) + aabb.min.z;
	aabbWorld.m[3][3] = 1.0f;

	// 半径
	Vector3 aabbRadius = aabb.max - Vector3(aabbWorld.m[3][0], aabbWorld.m[3][1], aabbWorld.m[3][2]);

	// ローカル座標
	Vector3 local1[8];
	local1[0] = { -aabbRadius.x , -aabbRadius.y , -aabbRadius.z };
	local1[1] = { aabbRadius.x , -aabbRadius.y , -aabbRadius.z };
	local1[2] = { -aabbRadius.x , -aabbRadius.y , aabbRadius.z };
	local1[3] = { aabbRadius.x , -aabbRadius.y , aabbRadius.z };
	local1[4] = { -aabbRadius.x , aabbRadius.y , -aabbRadius.z };
	local1[5] = { aabbRadius.x , aabbRadius.y , -aabbRadius.z };
	local1[6] = { -aabbRadius.x , aabbRadius.y , aabbRadius.z };
	local1[7] = { aabbRadius.x , aabbRadius.y , aabbRadius.z };


	// ワールド座標
	Vector3 world1[8];
	for (uint32_t i = 0; i < 8; i++)
	{
		world1[i] = Transform(local1[i], aabbWorld);
	}


	/*   OBB   */

	// ワールド行列
	Matrix4x4 obbWorld;

	obbWorld.m[0][0] = obb.oriented[0].x;
	obbWorld.m[0][1] = obb.oriented[0].y;
	obbWorld.m[0][2] = obb.oriented[0].z;
	obbWorld.m[0][3] = 0.0f;

	obbWorld.m[1][0] = obb.oriented[1].x;
	obbWorld.m[1][1] = obb.oriented[1].y;
	obbWorld.m[1][2] = obb.oriented[1].z;
	obbWorld.m[1][3] = 0.0f;

	obbWorld.m[2][0] = obb.oriented[2].x;
	obbWorld.m[2][1] = obb.oriented[2].y;
	obbWorld.m[2][2] = obb.oriented[2].z;
	obbWorld.m[2][3] = 0.0f;

	obbWorld.m[3][0] = obb.center.x;
	obbWorld.m[3][1] = obb.center.y;
	obbWorld.m[3][2] = obb.center.z;
	obbWorld.m[3][3] = 1.0f;


	// ローカル座標
	Vector3 local2[8];
	local2[0] = { -obb.size.x , -obb.size.y , -obb.size.z };
	local2[1] = { obb.size.x , -obb.size.y , -obb.size.z };
	local2[2] = { -obb.size.x , -obb.size.y , obb.size.z };
	local2[3] = { obb.size.x , -obb.size.y , obb.size.z };
	local2[4] = { -obb.size.x , obb.size.y , -obb.size.z };
	local2[5] = { obb.size.x , obb.size.y , -obb.size.z };
	local2[6] = { -obb.size.x , obb.size.y , obb.size.z };
	local2[7] = { obb.size.x , obb.size.y , obb.size.z };


	// ワールド座標
	Vector3 world2[8];
	for (uint32_t i = 0; i < 8; i++)
	{
		world2[i] = Transform(local2[i], obbWorld);
	}


	/*------------
		分離軸
	------------*/

	/*   面法線 AABB X   */

	Vector3 normal = Vector3(1.0f, 0.0f, 0.0f);

	float min1 = Dot(world1[0], normal);
	float max1 = Dot(world1[0], normal);

	float min2 = Dot(world2[0], normal);
	float max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	float sumSpan = (max1 - min1) + (max2 - min2);
	float longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 AABB Y   */

	normal = Vector3(0.0f, 1.0f, 0.0f);

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 AABB Z   */

	normal = Vector3(0.0f, 0.0f, 1.0f);

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB X   */

	normal = obb.oriented[0];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB Y   */

	normal = obb.oriented[1];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   面法線 OBB Z   */

	normal = obb.oriented[2];

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : X , OBB : X   */

	normal = Normalize(Cross(Vector3(1.0f, 0.0f, 0.0f), obb.oriented[0]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : X , OBB : Y   */

	normal = Normalize(Cross(Vector3(1.0f, 0.0f, 0.0f), obb.oriented[1]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : X , OBB : Z   */

	normal = Normalize(Cross(Vector3(1.0f, 0.0f, 0.0f), obb.oriented[2]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : Y , OBB : X   */

	normal = Normalize(Cross(Vector3(0.0f, 1.0f, 0.0f), obb.oriented[0]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : Y , OBB : Y   */

	normal = Normalize(Cross(Vector3(0.0f, 1.0f, 0.0f), obb.oriented[1]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : Y , OBB : Z   */

	normal = Normalize(Cross(Vector3(0.0f, 1.0f, 0.0f), obb.oriented[2]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : Z , OBB : X   */

	normal = Normalize(Cross(Vector3(0.0f, 0.0f, 1.0f), obb.oriented[0]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : Z , OBB : Y   */

	normal = Normalize(Cross(Vector3(0.0f, 0.0f, 1.0f), obb.oriented[1]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	/*   クロス積 AABB : Z , OBB : Z   */

	normal = Normalize(Cross(Vector3(0.0f, 0.0f, 1.0f), obb.oriented[2]));

	min1 = Dot(world1[0], normal);
	max1 = Dot(world1[0], normal);

	min2 = Dot(world2[0], normal);
	max2 = Dot(world2[0], normal);

	for (uint32_t i = 1; i < 8; i++)
	{
		float proj1 = Dot(world1[i], normal);
		float proj2 = Dot(world2[i], normal);

		min1 = std::min(min1, proj1);
		max1 = std::max(max1, proj1);

		min2 = std::min(min2, proj2);
		max2 = std::max(max2, proj2);
	}

	sumSpan = (max1 - min1) + (max2 - min2);
	longSpan = (std::max)(max1, max2) - (std::min)(min1, min2);

	if (sumSpan < longSpan)
		return false;


	return true;
}



/// <summary>
/// 衝突判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="sphere">球</param>
/// <returns></returns>
bool Collision::IsCollision(const AABB& aabb, const Sphere& sphere)
{
	// 最近接点
	Vector3 clossetPoint;
	clossetPoint.x = std::clamp(sphere.center.x, aabb.min.x, aabb.max.x);
	clossetPoint.y = std::clamp(sphere.center.y, aabb.min.y, aabb.max.y);
	clossetPoint.z = std::clamp(sphere.center.z, aabb.min.z, aabb.max.z);

	// 最近接点が半径より小さいとき
	if (sphere.radius >= Length(sphere.center - clossetPoint))
	{
		return true;
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="obb">OBB</param>
/// <param name="sphere">球</param>
bool Collision::IsCollision(const OBB& obb, const Sphere& sphere)
{
	// ワールド行列
	Matrix4x4 obbWorld;

	obbWorld.m[0][0] = obb.oriented[0].x;
	obbWorld.m[0][1] = obb.oriented[0].y;
	obbWorld.m[0][2] = obb.oriented[0].z;
	obbWorld.m[0][3] = 0.0f;

	obbWorld.m[1][0] = obb.oriented[1].x;
	obbWorld.m[1][1] = obb.oriented[1].y;
	obbWorld.m[1][2] = obb.oriented[1].z;
	obbWorld.m[1][3] = 0.0f;

	obbWorld.m[2][0] = obb.oriented[2].x;
	obbWorld.m[2][1] = obb.oriented[2].y;
	obbWorld.m[2][2] = obb.oriented[2].z;
	obbWorld.m[2][3] = 0.0f;

	obbWorld.m[3][0] = obb.center.x;
	obbWorld.m[3][1] = obb.center.y;
	obbWorld.m[3][2] = obb.center.z;
	obbWorld.m[3][3] = 1.0f;


	// OBBのワールド逆行列
	Matrix4x4 inverseMatrix = MakeInverseMatrix4x4(obbWorld);

	// 球をOBBの座標に持ち込む
	Vector3 centerInOBBLocalSpace = Transform(sphere.center, inverseMatrix);

	// OBB視点のため、AABBを使用する
	AABB aabbOBBLocal =
	{
		{-obb.size.x,-obb.size.y,-obb.size.z},
		{obb.size.x,obb.size.y,obb.size.z}
	};

	// OBB視点の球
	Sphere sphereOBBLocal =
	{
		centerInOBBLocalSpace,
		sphere.radius
	};

	// AABBと球の当たり判定
	return IsCollision(aabbOBBLocal, sphereOBBLocal);
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="sphere">球</param>
/// <param name="plane">平面</param>
/// <returns></returns>
bool Collision::IsCollision(const Sphere& sphere, const Plane& plane)
{
	// 平面方程式で距離を求める
	float distance = Dot(sphere.center, plane.normal) - plane.distance;

	// 距離が半径より小さいとき
	if (std::fabs(distance) <= sphere.radius)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="plane">平面</param>
/// <param name="line">直線</param>
/// <returns></returns>
bool Collision::IsCollision(const Plane& plane, const Line& line)
{
	// 法線と終点方向の内積
	float NdotD = Dot(plane.normal, line.diff);

	// 垂直の場合当たらない
	if (NdotD == 0.0f)
	{
		return false;
	}

	return true;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="plane">平面</param>
/// <param name="ray">半直線</param>
/// <returns></returns>
bool Collision::IsCollision(const Plane& plane, const Ray& ray)
{
	// 法線と終点方向の内積
	float NdotD = Dot(plane.normal, ray.diff);

	// 垂直の場合当たらない
	if (NdotD == 0.0f)
	{
		return false;
	}

	// 法線と始点の内積
	float NdotO = Dot(plane.normal, ray.origin);

	// 媒介変数を求める
	float t = (plane.distance - NdotO) / NdotD;

	if (t >= 0.0f)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="plane">平面</param>
/// <param name="segment">線分</param>
/// <returns></returns>
bool Collision::IsCollision(const Plane& plane, const Segment& segment)
{
	// 法線と終点方向の内積
	float NdotD = Dot(plane.normal, segment.diff);

	// 垂直の場合は当たらない
	if (NdotD == 0.0f)
	{
		return false;
	}

	// 法線と始点の内積
	float NdotO = Dot(plane.normal, segment.origin);

	// 媒介変数を求める
	float t = (plane.distance - NdotO) / NdotD;

	if (t >= 0.0f && t <= 1.0f)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="line">直線</param>
/// <returns></returns>
bool Collision::IsCollision(const Triangle& triangle, const Line& line)
{
	// 三角形の法線
	Vector3 normal = 
		Cross(triangle.vertices[1] - triangle.vertices[0], triangle.vertices[2] - triangle.vertices[1]);

	// 法線と終点方向の内積
	float NdotD = Dot(normal, line.diff);

	// 垂直の場合は当たらない
	if (NdotD == 0.0f)
	{
		return false;
	}

	// 法線と始点の内積
	float NdotO = Dot(normal, line.origin);

	// 距離
	float distance = Dot(triangle.vertices[0], normal);

	// 媒介変数を求める
	float t = (distance - NdotO) / NdotD;


	// 平面の最近接点
	Vector3 closetPoint = (t * line.diff) + line.origin;

	// 最近接点と頂点の法線
	Vector3 normal01p = Cross(triangle.vertices[1] - triangle.vertices[0], closetPoint - triangle.vertices[1]);
	Vector3 normal12p = Cross(triangle.vertices[2] - triangle.vertices[1], closetPoint - triangle.vertices[2]);
	Vector3 normal20p = Cross(triangle.vertices[0] - triangle.vertices[2], closetPoint - triangle.vertices[0]);

	// 内積で判定する
	if (Dot(normal01p, normal) >= 0.0f &&
		Dot(normal12p, normal) >= 0.0f &&
		Dot(normal20p, normal) >= 0.0f)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="ray">半直線</param>
/// <returns></returns>
bool Collision::IsCollision(const Triangle& triangle, const Ray& ray)
{
	// 三角形の法線
	Vector3 normal =
		Cross(triangle.vertices[1] - triangle.vertices[0], triangle.vertices[2] - triangle.vertices[1]);

	// 法線と終点方向の内積
	float NdotD = Dot(normal, ray.diff);

	// 垂直の場合は当たらない
	if (NdotD == 0.0f)
	{
		return false;
	}

	// 法線と始点の内積
	float NdotO = Dot(normal, ray.origin);

	// 距離
	float distance = Dot(triangle.vertices[0], normal);

	// 媒介変数を求める
	float t = (distance - NdotO) / NdotD;

	if (t >= 0.0f)
	{
		// 平面の最近接点
		Vector3 closetPoint = (t * ray.diff) + ray.origin;

		// 最近接点と頂点の法線
		Vector3 normal01p = Cross(triangle.vertices[1] - triangle.vertices[0], closetPoint - triangle.vertices[1]);
		Vector3 normal12p = Cross(triangle.vertices[2] - triangle.vertices[1], closetPoint - triangle.vertices[2]);
		Vector3 normal20p = Cross(triangle.vertices[0] - triangle.vertices[2], closetPoint - triangle.vertices[0]);

		// 内積で判定する
		if (Dot(normal01p, normal) >= 0.0f &&
			Dot(normal12p, normal) >= 0.0f &&
			Dot(normal20p, normal) >= 0.0f)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="segment">線分</param>
/// <returns></returns>
bool Collision::IsCollision(const Triangle& triangle, const Segment& segment)
{
	// 三角形の法線
	Vector3 normal =
		Cross(triangle.vertices[1] - triangle.vertices[0], triangle.vertices[2] - triangle.vertices[1]);

	// 法線と終点方向の内積
	float NdotD = Dot(normal, segment.diff);

	// 垂直の場合は当たらない
	if (NdotD == 0.0f)
	{
		return false;
	}

	// 法線と始点の内積
	float NdotO = Dot(normal, segment.origin);

	// 距離
	float distance = Dot(triangle.vertices[0], normal);

	// 媒介変数を求める
	float t = (distance - NdotO) / NdotD;

	if (t >= 0.0f && t <= 1.0f)
	{
		// 平面の最近接点
		Vector3 closetPoint = (t * segment.diff) + segment.origin;

		// 最近接点と頂点の法線
		Vector3 normal01p = Cross(triangle.vertices[1] - triangle.vertices[0], closetPoint - triangle.vertices[1]);
		Vector3 normal12p = Cross(triangle.vertices[2] - triangle.vertices[1], closetPoint - triangle.vertices[2]);
		Vector3 normal20p = Cross(triangle.vertices[0] - triangle.vertices[2], closetPoint - triangle.vertices[0]);

		// 内積で判定する
		if (Dot(normal01p, normal) >= 0.0f &&
			Dot(normal12p, normal) >= 0.0f &&
			Dot(normal20p, normal) >= 0.0f)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="line">直線</param>
/// <returns></returns>
bool Collision::IsCollision(const AABB& aabb, const Line& line)
{
	Vector3 tMin =
	{
		(aabb.min.x - line.origin.x) / line.diff.x,
		(aabb.min.y - line.origin.y) / line.diff.y,
		(aabb.min.z - line.origin.z) / line.diff.z
	};

	Vector3 tMax =
	{
		(aabb.max.x - line.origin.x) / line.diff.x,
		(aabb.max.y - line.origin.y) / line.diff.y,
		(aabb.max.z - line.origin.z) / line.diff.z
	};

	Vector3 tNear =
	{
		std::min(tMin.x , tMax.x),
		std::min(tMin.y , tMax.y),
		std::min(tMin.z , tMax.z)
	};

	Vector3 tFar =
	{
		std::max(tMin.x , tMax.x),
		std::max(tMin.y , tMax.y),
		std::max(tMin.z , tMax.z)
	};

	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="ray">半直線</param>
/// <returns></returns>
bool Collision::IsCollision(const AABB& aabb, const Ray& ray)
{
	Vector3 tMin =
	{
		(aabb.min.x - ray.origin.x) / ray.diff.x,
		(aabb.min.y - ray.origin.y) / ray.diff.y,
		(aabb.min.z - ray.origin.z) / ray.diff.z
	};

	Vector3 tMax =
	{
		(aabb.max.x - ray.origin.x) / ray.diff.x,
		(aabb.max.y - ray.origin.y) / ray.diff.y,
		(aabb.max.z - ray.origin.z) / ray.diff.z
	};

	Vector3 tNear =
	{
		std::min(tMin.x , tMax.x),
		std::min(tMin.y , tMax.y),
		std::min(tMin.z , tMax.z)
	};

	Vector3 tFar =
	{
		std::max(tMin.x , tMax.x),
		std::max(tMin.y , tMax.y),
		std::max(tMin.z , tMax.z)
	};

	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmax >= 0.0f)
	{
		if (tmin <= tmax)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="aabb">AABB</param>
/// <param name="segment">線分</param>
/// <returns></returns>
bool Collision::IsCollision(const AABB& aabb, const Segment& segment)
{
	Vector3 tMin =
	{
		(aabb.min.x - segment.origin.x) / segment.diff.x,
		(aabb.min.y - segment.origin.y) / segment.diff.y,
		(aabb.min.z - segment.origin.z) / segment.diff.z
	};

	Vector3 tMax =
	{
		(aabb.max.x - segment.origin.x) / segment.diff.x,
		(aabb.max.y - segment.origin.y) / segment.diff.y,
		(aabb.max.z - segment.origin.z) / segment.diff.z
	};

	Vector3 tNear =
	{
		std::min(tMin.x , tMax.x),
		std::min(tMin.y , tMax.y),
		std::min(tMin.z , tMax.z)
	};

	Vector3 tFar =
	{
		std::max(tMin.x , tMax.x),
		std::max(tMin.y , tMax.y),
		std::max(tMin.z , tMax.z)
	};

	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmax >= 0.0f && tmin <= 1.0f)
	{
		if (tmin <= tmax)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="obb">OBB</param>
/// <param name="line">直線</param>
/// <returns></returns>
bool Collision::IsCollision(const OBB& obb, const Line& line)
{
	// OBBのワールド行列
	Matrix4x4 obbWorld;

	obbWorld.m[0][0] = obb.oriented[0].x;
	obbWorld.m[0][1] = obb.oriented[0].y;
	obbWorld.m[0][2] = obb.oriented[0].z;
	obbWorld.m[0][3] = 0.0f;

	obbWorld.m[1][0] = obb.oriented[1].x;
	obbWorld.m[1][1] = obb.oriented[1].y;
	obbWorld.m[1][2] = obb.oriented[1].z;
	obbWorld.m[1][3] = 0.0f;

	obbWorld.m[2][0] = obb.oriented[2].x;
	obbWorld.m[2][1] = obb.oriented[2].y;
	obbWorld.m[2][2] = obb.oriented[2].z;
	obbWorld.m[2][3] = 0.0f;

	obbWorld.m[3][0] = obb.center.x;
	obbWorld.m[3][1] = obb.center.y;
	obbWorld.m[3][2] = obb.center.z;
	obbWorld.m[3][3] = 1.0f;


	// 逆行列
	Matrix4x4 obbInverse = MakeInverseMatrix4x4(obbWorld);

	// OBBのワールド座標に持ち込む
	Vector3 localOrigin = Transform(line.origin, obbInverse);
	Vector3 localEnd = Transform(line.origin + line.diff, obbInverse);

	// OBB視点のためAABBを使用する
	AABB localAABB
	{
		.min{-obb.size.x,-obb.size.y,-obb.size.z},
		.max{obb.size.x,obb.size.y,obb.size.z}
	};

	// OBB視点の直線
	Line localLine;
	localLine.origin = localOrigin;
	localLine.diff = localEnd - localOrigin;

	// AABBと直線の当たり判定
	return IsCollision(localAABB, localLine);
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="obb">OBB</param>
/// <param name="ray">半直線</param>
/// <returns></returns>
bool Collision::IsCollision(const OBB& obb, const Ray& ray)
{
	// OBBのワールド行列
	Matrix4x4 obbWorld;

	obbWorld.m[0][0] = obb.oriented[0].x;
	obbWorld.m[0][1] = obb.oriented[0].y;
	obbWorld.m[0][2] = obb.oriented[0].z;
	obbWorld.m[0][3] = 0.0f;

	obbWorld.m[1][0] = obb.oriented[1].x;
	obbWorld.m[1][1] = obb.oriented[1].y;
	obbWorld.m[1][2] = obb.oriented[1].z;
	obbWorld.m[1][3] = 0.0f;

	obbWorld.m[2][0] = obb.oriented[2].x;
	obbWorld.m[2][1] = obb.oriented[2].y;
	obbWorld.m[2][2] = obb.oriented[2].z;
	obbWorld.m[2][3] = 0.0f;

	obbWorld.m[3][0] = obb.center.x;
	obbWorld.m[3][1] = obb.center.y;
	obbWorld.m[3][2] = obb.center.z;
	obbWorld.m[3][3] = 1.0f;


	// 逆行列
	Matrix4x4 obbInverse = MakeInverseMatrix4x4(obbWorld);

	// OBBのワールド座標に持ち込む
	Vector3 localOrigin = Transform(ray.origin, obbInverse);
	Vector3 localEnd = Transform(ray.origin + ray.diff, obbInverse);

	// OBB視点のためAABBを使用する
	AABB localAABB
	{
		.min{-obb.size.x,-obb.size.y,-obb.size.z},
		.max{obb.size.x,obb.size.y,obb.size.z}
	};

	// OBB視点の半直線
	Ray localRay;
	localRay.origin = localOrigin;
	localRay.diff = localEnd - localOrigin;

	// AABBと半直線の当たり判定
	return IsCollision(localAABB, localRay);
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="obb">OBB</param>
/// <param name="segment">線分</param>
/// <returns></returns>
bool Collision::IsCollision(const OBB& obb, const Segment& segment)
{
	// OBBのワールド行列
	Matrix4x4 obbWorld;

	obbWorld.m[0][0] = obb.oriented[0].x;
	obbWorld.m[0][1] = obb.oriented[0].y;
	obbWorld.m[0][2] = obb.oriented[0].z;
	obbWorld.m[0][3] = 0.0f;

	obbWorld.m[1][0] = obb.oriented[1].x;
	obbWorld.m[1][1] = obb.oriented[1].y;
	obbWorld.m[1][2] = obb.oriented[1].z;
	obbWorld.m[1][3] = 0.0f;

	obbWorld.m[2][0] = obb.oriented[2].x;
	obbWorld.m[2][1] = obb.oriented[2].y;
	obbWorld.m[2][2] = obb.oriented[2].z;
	obbWorld.m[2][3] = 0.0f;

	obbWorld.m[3][0] = obb.center.x;
	obbWorld.m[3][1] = obb.center.y;
	obbWorld.m[3][2] = obb.center.z;
	obbWorld.m[3][3] = 1.0f;


	// 逆行列
	Matrix4x4 obbInverse = MakeInverseMatrix4x4(obbWorld);

	// OBBのワールド座標に持ち込む
	Vector3 localOrigin = Transform(segment.origin, obbInverse);
	Vector3 localEnd = Transform(segment.origin + segment.diff, obbInverse);

	// OBB視点のためAABBを使用する
	AABB localAABB
	{
		.min{-obb.size.x,-obb.size.y,-obb.size.z},
		.max{obb.size.x,obb.size.y,obb.size.z}
	};

	// OBB視点の線分
	Segment localSegment;
	localSegment.origin = localOrigin;
	localSegment.diff = localEnd - localOrigin;

	// AABBと線分の当たり判定
	return IsCollision(localAABB, localSegment);
}