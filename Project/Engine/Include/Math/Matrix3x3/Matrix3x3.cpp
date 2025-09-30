#include "Matrix3x3.h"

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector2 Transform(const Vector2& vector, const Matrix3x3& matrix)
{
	// 座標変換した値
	Vector2 transform;

	transform.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[0][1] + 1.0f * matrix.m[0][2];
	transform.y = vector.x * matrix.m[1][0] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[1][2];
	float w = vector.x * matrix.m[2][0] + vector.y * matrix.m[2][1] + 1.0f * matrix.m[2][2];

	assert(w != 0.0f);
	transform /= w;

	return transform;
}

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector3 Transform(const Vector3& vector, const Matrix3x3& matrix)
{
	// 座標変換した値
	Vector3 transform;

	transform.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[0][1] + vector.z * matrix.m[0][2];
	transform.y = vector.x * matrix.m[1][0] + vector.y * matrix.m[1][1] + vector.z * matrix.m[1][2];
	transform.z = vector.x * matrix.m[2][0] + vector.y * matrix.m[2][1] + vector.z * matrix.m[2][2];

	assert(transform.z != 0.0f);
	transform.x /= transform.z;
	transform.y /= transform.z;
	transform.z /= transform.z;

	return transform;
}

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector2 TransformNormal(const Vector2& vector, const Matrix3x3& matrix)
{
	// 座標変換した値
	Vector2 transform;

	transform.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[0][1];
	transform.y = vector.x * matrix.m[1][0] + vector.y * matrix.m[1][1];

	return transform;
}

/// <summary>
/// 単位行列を作成する
/// </summary>
/// <returns></returns>
Matrix3x3 MakeIdentityMatrix3x3()
{
	// 単位行列
	Matrix3x3 identityMatrix;

	for (uint32_t i = 0; i < 3; ++i)
	{
		for (uint32_t j = 0; j < 3; ++j)
		{
			if (i == j)
			{
				identityMatrix.m[i][j] = 1.0f;
			} else
			{
				identityMatrix.m[i][j] = 0.0f;
			}
		}
	}

	return identityMatrix;
}

/// <summary>
/// 転置行列を作成する
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
Matrix3x3 MakeTransposeMatrix(const Matrix3x3& matrix)
{
	// 転置行列
	Matrix3x3 transposeMatrix;

	transposeMatrix.m[0][0] = matrix.m[0][0];
	transposeMatrix.m[0][1] = matrix.m[1][0];
	transposeMatrix.m[0][2] = matrix.m[2][0];

	transposeMatrix.m[1][0] = matrix.m[0][1];
	transposeMatrix.m[1][1] = matrix.m[1][1];
	transposeMatrix.m[1][2] = matrix.m[2][1];

	transposeMatrix.m[2][0] = matrix.m[0][2];
	transposeMatrix.m[2][1] = matrix.m[1][2];
	transposeMatrix.m[2][2] = matrix.m[2][2];

	return transposeMatrix;
}

/// <summary>
/// 拡大縮小行列を作成する
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix3x3 MakeScaleMatrix(const Vector2& scale)
{
	// 拡大縮小行列
	Matrix3x3 scaleMatrix;

	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[0][1] = 0.0f;
	scaleMatrix.m[0][2] = 0.0f;

	scaleMatrix.m[1][0] = 0.0f;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[1][2] = 0.0f;

	scaleMatrix.m[2][0] = 0.0f;
	scaleMatrix.m[2][1] = 0.0f;
	scaleMatrix.m[2][2] = 1.0f;

	return scaleMatrix;
}

/// <summary>
/// 回転行列を作成する
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix3x3 MakeRotateMatrix(float radian)
{
	// 回転行列
	Matrix3x3 rotateMatrix;

	rotateMatrix.m[0][0] = std::cos(radian);
	rotateMatrix.m[0][1] = std::sin(radian);
	rotateMatrix.m[0][2] = 0.0f;

	rotateMatrix.m[1][0] = -std::sin(radian);
	rotateMatrix.m[1][1] = std::cos(radian);
	rotateMatrix.m[1][2] = 0.0f;

	rotateMatrix.m[2][0] = 0.0f;
	rotateMatrix.m[2][1] = 0.0f;
	rotateMatrix.m[2][2] = 1.0f;

	return rotateMatrix;
}

/// <summary>
/// 平行移動行列を作成する
/// </summary>
/// <param name="translation"></param>
/// <returns></returns>
Matrix3x3 MakeTranslateMatrix(const Vector2& translation)
{
	// 平行移動行列
	Matrix3x3 translateMatrix;

	translateMatrix.m[0][0] = 1.0f;
	translateMatrix.m[0][1] = 0.0f;
	translateMatrix.m[0][2] = 0.0f;

	translateMatrix.m[1][0] = 0.0f;
	translateMatrix.m[1][1] = 1.0f;
	translateMatrix.m[1][2] = 0.0f;
	
	translateMatrix.m[2][0] = translation.x;
	translateMatrix.m[2][1] = translation.y;
	translateMatrix.m[2][2] = 1.0f;

	return translateMatrix;
}

/// <summary>
/// アフィン変換行列を作成する
/// </summary>
/// <param name="scale"></param>
/// <param name="radian"></param>
/// <param name="translation"></param>
/// <returns></returns>
Matrix3x3 MakeAffineMatrix(const Vector2& scale, float radian, const Vector2& translation)
{
	// アフィン変換行列
	Matrix3x3 affineMatrix = MakeScaleMatrix(scale) * MakeRotateMatrix(radian) * MakeTranslateMatrix(translation);
	return affineMatrix;
}

/// <summary>
/// 逆行列を作成する
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix3x3 MakeInverseMatrix(const Matrix3x3& m)
{
	// 行列式
	float determinant =
		m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1];

	// 余因子行列
	Matrix3x3 adjugateMatrix;

	adjugateMatrix.m[0][0] = m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1];
	adjugateMatrix.m[0][1] = -(m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1]);
	adjugateMatrix.m[0][2] = m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1];

	adjugateMatrix.m[1][0] = -(m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]);
	adjugateMatrix.m[1][1] = m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0];
	adjugateMatrix.m[1][2] = -(m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0]);

	adjugateMatrix.m[2][0] = m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0];
	adjugateMatrix.m[2][1] = -(m.m[0][0] * m.m[2][1] - m.m[0][1] * m.m[2][0]);
	adjugateMatrix.m[2][2] = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];

	for (int32_t i = 0; i < 3; ++i)
	{
		for (int32_t j = 0; j < 3; ++j)
		{
			adjugateMatrix.m[i][j] *= 1.0f / determinant;
		}
	}

	return adjugateMatrix;
}

/// <summary>
/// 平行投影行列を作成する
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="right"></param>
/// <param name="bottom"></param>
/// <returns></returns>
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	// 平行投影行列
	Matrix3x3 orthographicMatrix;

	orthographicMatrix.m[0][0] = 2.0f / (right - left);
	orthographicMatrix.m[0][1] = 0.0f;
	orthographicMatrix.m[0][2] = 0.0f;

	orthographicMatrix.m[1][0] = 0.0f;
	orthographicMatrix.m[1][1] = 2.0f / (top - bottom);
	orthographicMatrix.m[1][2] = 0.0f;

	orthographicMatrix.m[2][0] = (left + right) / (left - right);
	orthographicMatrix.m[2][1] = (top + bottom) / (bottom - top);
	orthographicMatrix.m[2][2] = 1.0f;

	return orthographicMatrix;
}

/// <summary>
/// ビューポート変換行列を作成する
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <returns></returns>
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height)
{
	// ビューポート変換行列
	Matrix3x3 viewportMatrix;

	viewportMatrix.m[0][0] = width / 2.0f;
	viewportMatrix.m[0][1] = 0.0f;
	viewportMatrix.m[0][2] = 0.0f;

	viewportMatrix.m[1][0] = 0.0f;
	viewportMatrix.m[1][1] = -(height / 2.0f);
	viewportMatrix.m[1][2] = 0.0f;

	viewportMatrix.m[2][0] = left + (width / 2.0f);
	viewportMatrix.m[2][1] = top + (height / 2.0f);
	viewportMatrix.m[2][2] = 1.0f;

	return viewportMatrix;
}