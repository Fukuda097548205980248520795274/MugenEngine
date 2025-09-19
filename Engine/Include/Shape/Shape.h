#pragma once
#include "../Math/Vector3/Vector3.h"

// 球
struct Sphere
{
	// 中心点
	Vector3 center;

	// 半径
	float radius;
};

// 平面
struct Plane
{
	// 向き
	Vector3 normal;

	// 距離
	float distance;
};

// 直線
struct Line
{
	// 始点
	Vector3 origin;

	// 終点（差分ベクトル）
	Vector3 diff;
};

// 半直線
struct Ray
{
	// 始点
	Vector3 origin;

	// 終点（差分ベクトル）
	Vector3 diff;
};

// 線分
struct Segment
{
	// 始点
	Vector3 origin;

	// 終点（差分ベクトル）
	Vector3 diff;
};

// 三角形
struct Triangle
{
	// 頂点
	Vector3 vertices[3];
};

// AABB
struct AABB
{
	// 最小点
	Vector3 min;

	// 最大点
	Vector3 max;
};

// OBB
struct OBB
{
	// 中心点
	Vector3 center;

	// 回転行列
	Vector3 oriented[3];

	// 大きさ
	Vector3 size;
};