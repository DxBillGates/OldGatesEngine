#include "..\..\Header\Math\Matrix4.h"
#include <cmath>

using Vector3 = GatesEngine::Math::Vector3;

GatesEngine::Math::Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m[i][j] = 0;
		}
	}
}

GatesEngine::Math::Matrix4x4::Matrix4x4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
	: _11(m00), _12(m01), _13(m02), _14(m03),
	_21(m10), _22(m11), _23(m12), _24(m13),
	_31(m20), _32(m21), _33(m22), _34(m23),
	_41(m30), _42(m31), _43(m32), _44(m33)
{
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::Identity()
{
	Matrix4x4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};

	return result;
}

GatesEngine::Math::Axis GatesEngine::Math::Matrix4x4::GetAxis(const Matrix4x4& m)
{
	Axis result;
	result.x = Vector3(m._11, m._12, m._13);
	result.y = Vector3(m._21, m._22, m._23);
	result.z = Vector3(m._31, m._32, m._33);
	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::Scale(const Vector3 & v)
{
	Matrix4x4 result
	{
		v.x,0.0f,0.0f,0.0f,
		0.0f,v.y,0.0f,0.0f,
		0.0f,0.0f,v.z,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};

	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::RotationX(float angle)
{
	float sin = std::sinf(angle);
	float cos = std::cosf(angle);

	Matrix4x4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cos,sin,0.0f,
		0.0f,-sin,cos,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};

	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::RotationY(float angle)
{
	float sin = std::sinf(angle);
	float cos = std::cosf(angle);

	Matrix4x4 result
	{
		cos,0.0f,-sin,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		sin,0.0f,cos,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};

	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::RotationZ(float angle)
{
	float sin = std::sinf(angle);
	float cos = std::cosf(angle);

	Matrix4x4 result
	{
		cos,sin,0.0f,0.0f,
		-sin,cos,0.0f ,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};

	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::Translate(const Vector3 & v)
{
	Matrix4x4 result
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		v.x,v.y,v.z,1.0f,
	};

	return result;
}

Vector3 GatesEngine::Math::Matrix4x4::Transform(const Vector3 & v, const Matrix4x4 & m)
{
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

	Vector3 result
	{
		(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
		(v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
		(v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w,
	};

	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::Transpose(const Matrix4x4 & m)
{
	Matrix4x4 result;
	result =
	{
		m.m[0][0],m.m[1][0],m.m[2][0],m.m[3][0],
		m.m[0][1],m.m[1][1],m.m[2][1],m.m[3][1],
		m.m[0][2],m.m[1][2],m.m[2][2],m.m[3][2],
		m.m[0][3],m.m[1][3],m.m[2][3],m.m[3][3],
	};
	return result;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::Matrix4x4::Inverse(const Matrix4x4 & m)
{
	Matrix4x4 result;
	result.m[0][0] = m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2];
	result.m[0][1] = -m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2];
	result.m[0][2] = m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2];
	result.m[0][3] = -m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2];

	result.m[1][0] = -m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2];
	result.m[1][1] = m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2];
	result.m[1][2] = -m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2];
	result.m[1][3] = m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2];

	result.m[2][0] = m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1];
	result.m[2][1] = -m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1];
	result.m[2][2] = m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1];
	result.m[2][3] = -m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1];

	result.m[3][0] = -m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1];
	result.m[3][1] = m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1];
	result.m[3][2] = -m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1];
	result.m[3][3] = m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1];

	float f = Matrix4x4::Determinant(m);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] *= 1.0f / f;
		}
	}
	return result;
}

float GatesEngine::Math::Matrix4x4::Determinant(const Matrix4x4 & m)
{
	float f0 = m.m[0][0] * ((m.m[1][1] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) - (m.m[1][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1])) + (m.m[1][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1]))));
	float f1 = m.m[1][0] * ((m.m[0][1] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) - (m.m[0][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1])) + (m.m[0][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1]))));
	float f2 = m.m[2][0] * ((m.m[0][1] * (m.m[1][2] * m.m[3][3] - m.m[1][3] * m.m[3][2]) - (m.m[0][2] * (m.m[1][1] * m.m[3][3] - m.m[1][3] * m.m[3][1])) + (m.m[0][3] * (m.m[1][1] * m.m[3][2] - m.m[1][2] * m.m[3][1]))));
	float f3 = m.m[3][0] * ((m.m[0][1] * (m.m[1][2] * m.m[2][3] - m.m[1][3] * m.m[2][2]) - (m.m[0][2] * (m.m[1][1] * m.m[2][3] - m.m[1][3] * m.m[2][1])) + (m.m[0][3] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]))));
	float result = f0 - f1 + f2 - f3;
	return result;
}

GatesEngine::Math::Axis GatesEngine::Math::Matrix4x4::GetAxis()
{
	return GetAxis(*this);
}

GatesEngine::Math::Matrix4x4 & GatesEngine::Math::operator*=(Matrix4x4 & m1, const Matrix4x4 & m2)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	m1 = result;
	return m1;
}

GatesEngine::Math::Matrix4x4 GatesEngine::Math::operator*(const Matrix4x4 & m1, const Matrix4x4 & m2)
{
	Matrix4x4 result = m1;
	return result *= m2;
}

Vector3 GatesEngine::Math::operator*(const Vector3 & v, const Matrix4x4 & m)
{
	return Matrix4x4::Transform(v, m);
}
