#pragma once
#include <cassert>
#include <cstdint>
#include <cmath>
#include "../Vector3/Vector3.h"
#include "../Vector4/Vector4.h"

// 4x4行列
struct Matrix4x4
{
	float m[4][4];

	// 加算
	Matrix4x4 operator+=(const Matrix4x4& matrix)
	{
		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				this->m[i][j] += matrix.m[i][j];
			}
		}

		return *this;
	}

	// 減算
	Matrix4x4 operator-=(const Matrix4x4& matrix)
	{
		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				this->m[i][j] -= matrix.m[i][j];
			}
		}

		return *this;
	}

	// スカラー倍
	Matrix4x4 operator*=(float scalar)
	{
		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				this->m[i][j] *= scalar;
			}
		}

		return *this;
	}

	// 乗算
	Matrix4x4 operator*=(const Matrix4x4& matrix)
	{
		// 積
		Matrix4x4 multiply;

		multiply.m[0][0] = this->m[0][0] * matrix.m[0][0] + this->m[0][1] * matrix.m[1][0] + this->m[0][2] * matrix.m[2][0] + this->m[0][3] * matrix.m[3][0];
		multiply.m[0][1] = this->m[0][0] * matrix.m[0][1] + this->m[0][1] * matrix.m[1][1] + this->m[0][2] * matrix.m[2][1] + this->m[0][3] * matrix.m[3][1];
		multiply.m[0][2] = this->m[0][0] * matrix.m[0][2] + this->m[0][1] * matrix.m[1][2] + this->m[0][2] * matrix.m[2][2] + this->m[0][3] * matrix.m[3][2];
		multiply.m[0][3] = this->m[0][0] * matrix.m[0][3] + this->m[0][1] * matrix.m[1][3] + this->m[0][2] * matrix.m[2][3] + this->m[0][3] * matrix.m[3][3];

		multiply.m[1][0] = this->m[1][0] * matrix.m[0][0] + this->m[1][1] * matrix.m[1][0] + this->m[1][2] * matrix.m[2][0] + this->m[1][3] * matrix.m[3][0];
		multiply.m[1][1] = this->m[1][0] * matrix.m[0][1] + this->m[1][1] * matrix.m[1][1] + this->m[1][2] * matrix.m[2][1] + this->m[1][3] * matrix.m[3][1];
		multiply.m[1][2] = this->m[1][0] * matrix.m[0][2] + this->m[1][1] * matrix.m[1][2] + this->m[1][2] * matrix.m[2][2] + this->m[1][3] * matrix.m[3][2];
		multiply.m[1][3] = this->m[1][0] * matrix.m[0][3] + this->m[1][1] * matrix.m[1][3] + this->m[1][2] * matrix.m[2][3] + this->m[1][3] * matrix.m[3][3];

		multiply.m[2][0] = this->m[2][0] * matrix.m[0][0] + this->m[2][1] * matrix.m[1][0] + this->m[2][2] * matrix.m[2][0] + this->m[2][3] * matrix.m[3][0];
		multiply.m[2][1] = this->m[2][0] * matrix.m[0][1] + this->m[2][1] * matrix.m[1][1] + this->m[2][2] * matrix.m[2][1] + this->m[2][3] * matrix.m[3][1];
		multiply.m[2][2] = this->m[2][0] * matrix.m[0][2] + this->m[2][1] * matrix.m[1][2] + this->m[2][2] * matrix.m[2][2] + this->m[2][3] * matrix.m[3][2];
		multiply.m[2][3] = this->m[2][0] * matrix.m[0][3] + this->m[2][1] * matrix.m[1][3] + this->m[2][2] * matrix.m[2][3] + this->m[2][3] * matrix.m[3][3];

		multiply.m[3][0] = this->m[3][0] * matrix.m[0][0] + this->m[3][1] * matrix.m[1][0] + this->m[3][2] * matrix.m[2][0] + this->m[3][3] * matrix.m[3][0];
		multiply.m[3][1] = this->m[3][0] * matrix.m[0][1] + this->m[3][1] * matrix.m[1][1] + this->m[3][2] * matrix.m[2][1] + this->m[3][3] * matrix.m[3][1];
		multiply.m[3][2] = this->m[3][0] * matrix.m[0][2] + this->m[3][1] * matrix.m[1][2] + this->m[3][2] * matrix.m[2][2] + this->m[3][3] * matrix.m[3][2];
		multiply.m[3][3] = this->m[3][0] * matrix.m[0][3] + this->m[3][1] * matrix.m[1][3] + this->m[3][2] * matrix.m[2][3] + this->m[3][3] * matrix.m[3][3];

		*this = multiply;

		return *this;
	}
};

namespace
{
	// 加算
	Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2)
	{
		// 加算
		Matrix4x4 add;

		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				add.m[i][j] = m1.m[i][j] + m2.m[i][j];
			}
		}

		return add;
	}

	// 減算
	Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2)
	{
		// 加算
		Matrix4x4 subtract;

		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				subtract.m[i][j] = m1.m[i][j] - m2.m[i][j];
			}
		}

		return subtract;
	}

	// スカラー倍
	Matrix4x4 operator*(float scalar, const Matrix4x4& matrix)
	{
		// スカラー倍
		Matrix4x4 scalarMultiply;

		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				scalarMultiply.m[i][j] = scalar * matrix.m[i][j];
			}
		}

		return scalarMultiply;
	}

	// スカラー倍
	Matrix4x4 operator*(const Matrix4x4& matrix, float scalar)
	{
		// スカラー倍
		Matrix4x4 scalarMultiply;

		for (uint32_t i = 0; i < 4; ++i)
		{
			for (uint32_t j = 0; j < 4; ++j)
			{
				scalarMultiply.m[i][j] = matrix.m[i][j] * scalar;
			}
		}

		return scalarMultiply;
	}

	// 乗算
	Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
	{
		// 積
		Matrix4x4 multiply;

		multiply.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
		multiply.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
		multiply.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
		multiply.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

		multiply.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
		multiply.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
		multiply.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
		multiply.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

		multiply.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
		multiply.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
		multiply.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
		multiply.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

		multiply.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
		multiply.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
		multiply.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
		multiply.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

		return multiply;
	}
}

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector4 Transform(const Vector4& vector, const Matrix4x4& matrix);

/// <summary>
/// 座標変換を行う
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns></returns>
Vector3 TransformNormal(const Vector3& vector, const Matrix4x4& matrix);

/// <summary>
/// 単位行列を作成する
/// </summary>
/// <returns></returns>
Matrix4x4 MakeIdentityMatrix4x4();

/// <summary>
/// 拡大縮小行列を作成する
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 Make3DScaleMatrix4x4(const Vector3& scale);

/// <summary>
/// X軸回転行列を作成する
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Make3DRotateXMatrix4x4(float radian);

/// <summary>
/// Y軸回転行列を作成する
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Make3DRotateYMatrix4x4(float radian);

/// <summary>
/// Z軸回転行列を作成する
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Make3DRotateZMatrix4x4(float radian);

/// <summary>
/// 回転行列を作成する
/// </summary>
/// <param name="rotation"></param>
/// <returns></returns>
Matrix4x4 Make3DRotateMatrix4x4(const Vector3& rotation);

/// <summary>
/// 平行移動行列を作成する
/// </summary>
/// <param name="translation"></param>
/// <returns></returns>
Matrix4x4 Make3DTranslateMatrix4x4(const Vector3& translation);

/// <summary>
/// アフィン変換行列を作成する
/// </summary>
/// <param name="scale"></param>
/// <param name="rotation"></param>
/// <param name="translation"></param>
/// <returns></returns>
Matrix4x4 Make3DAffineMatrix4x4(const Vector3& scale, const Vector3& rotation, const Vector3& translation);

/// <summary>
/// 逆行列を作成する
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 MakeInverseMatrix4x4(const Matrix4x4& m);

/// <summary>
/// 転置行列を作成する
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4x4 MakeTransposeMatrix4x4(const Matrix4x4& m);

/// <summary>
/// 透視投影行列を作成する
/// </summary>
/// <param name="fovY"></param>
/// <param name="aspectRatio"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns></returns>
Matrix4x4 MakePerspectiveFovMatrix4x4(float fovY, float aspectRatio, float nearClip, float farClip);

/// <summary>
/// 平行投影行列を作成する
/// </summary>
/// <param name="left"></param>
/// <param name="right"></param>
/// <param name="top"></param>
/// <param name="bottom"></param>
/// <param name="nearClip">近平面の距離</param>
/// <param name="farClip">遠平面の距離</param>
/// <returns></returns>
Matrix4x4 MakeOrthographicMatrix4x4(float left, float top, float right, float bottom, float nearClip, float farClip);

/// <summary>
/// ビューポート変換行列を作成する
/// </summary>
/// <param name="left"></param>
/// <param name="top"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="minDepth"></param>
/// <param name="maxDepth"></param>
/// <returns></returns>
Matrix4x4 MakeViewportMatrix4x4(float left, float top, float width, float height, float minDepth, float maxDepth);