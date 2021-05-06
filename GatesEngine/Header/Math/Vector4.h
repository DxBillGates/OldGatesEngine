#pragma once
namespace GatesEngine
{
	namespace Math
	{
		struct Vector4
		{
			float x, y, z, w;
			Vector4();
			Vector4(float xyzw);
			Vector4(float x, float y, float z, float w);

			Vector4 operator+();
			Vector4 operator-();
			Vector4& operator+=(const Vector4& v);
			Vector4& operator-=(const Vector4& v);
			Vector4& operator*=(float s);
			Vector4& operator/=(float s);
		};
		const Vector4 operator+(const Vector4& v1, const Vector4& v2);
		const Vector4 operator-(const Vector4& v1, const Vector4& v2);
		const Vector4 operator*(const Vector4& v, float s);
		const Vector4 operator*(float s, const Vector4& v);
		const Vector4 operator/(const Vector4& v, float s);
		const Vector4 operator/(float s, const Vector4& v);
	}
}
