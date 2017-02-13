#pragma once

namespace BG
{
	template<class T>
	struct Vector2
	{

		T x;
		T y;

		Vector2() : x(0), y(0) {}
		Vector2(const T &x, const T &y) : x(x), y(y) {}

		Vector2& operator+(const Vector2 &v) { x += v.x; y += v.y; return *this; }
		Vector2& operator+=(const Vector2 &v) { x += v.x; y += v.y; return *this; }

		Vector2& operator-(const Vector2 &v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator-=(const Vector2 &v) { x -= v.x; y -= v.y; return *this; }

		Vector2& operator*(const Vector2 &v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator*=(const Vector2 &v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator*(const T &scalar) { x *= scalar; y *= scalar; return *this; }

		Vector2& operator/(const Vector2 &v) { x /= v.x; y /= v.y; return *this; }
		Vector2& operator/=(const Vector2 &v) { x /= v.x; y /= v.y; return *this; }

		bool operator==(const Vector2 &v) { return x == v.x && y == v.y; }
		bool operator!=(const Vector2 &v) { return !(*this == v); }

	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<double> Vector2d;

}