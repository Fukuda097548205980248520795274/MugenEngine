#pragma once
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


private:

	// エンジン
	const MugenEngine* engine_ = nullptr;
};

