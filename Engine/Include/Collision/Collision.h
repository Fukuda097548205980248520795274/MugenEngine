#pragma once
#define NOMINMAX
#include <cassert>
#include "Shape/Sphere/Sphere.h"
#include "Shape/Plane/Plane.h"
#include "Shape/Triangle/Triangle.h"
#include "Shape/Line/Line.h"
#include "Shape/Ray/Ray.h"
#include "Shape/Segment/Segment.h"
#include "Shape/AABB/AABB.h"
#include "Shape/OBB/OBB.h"


// 前方宣言
class MugenEngine;

class Collision
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="engine"></param>
	void Initialize(const MugenEngine* engine);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="s1">球</param>
	/// <param name="s2">球</param>
	bool IsCollision(const Sphere& s1, const Sphere& s2);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb1">AABB</param>
	/// <param name="aabb2">AABB</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb1">OBB</param>
	/// <param name="obb2">OBB</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb1, const OBB& obb2);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="obb">OBB</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const OBB& obb);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="sphere">球</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Sphere& sphere);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="sphere">球</param>
	bool IsCollision(const OBB& obb, const Sphere& sphere);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <returns></returns>
	bool IsCollision(const Sphere& sphere, const Plane& plane);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Line& line);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Ray& ray);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const Plane& plane, const Segment& segment);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="triangle">三角形</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const Triangle& triangle, const Line& line);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="triangle">三角形</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const Triangle& triangle, const Ray& ray);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="triangle">三角形</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const Triangle& triangle, const Segment& segment);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Line& line);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Ray& ray);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="aabb">AABB</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const AABB& aabb, const Segment& segment);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="line">直線</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Line& line);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="ray">半直線</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Ray& ray);

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="obb">OBB</param>
	/// <param name="segment">線分</param>
	/// <returns></returns>
	bool IsCollision(const OBB& obb, const Segment& segment);


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;
};

