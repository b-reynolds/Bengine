#pragma once

template<class T>
class Vector2D
{

public:

	T x;
	T y;

	Vector2D() : x(0), y(0) {}
	Vector2D(const T &x, const T &y) : x(x), y(y) {}

	Vector2D& operator+(const Vector2D &v) { x += v.x; y += v.y; return *this; }
	Vector2D& operator+=(const Vector2D &v) { x += v.x; y += v.y; return *this; }
	Vector2D& operator-=(const Vector2D &v) { x -= v.x; y -= v.y; return *this; }
	Vector2D& operator*=(const Vector2D &v) { x *= v.x; y *= v.y; return *this; }
	Vector2D& operator/=(const Vector2D &v) { x /= v.x; y /= v.y; return *this; }
	bool operator==(const Vector2D &v) { return x == v.x && y == v.y; }
	bool operator!=(const Vector2D &v) { return !(*this == v); }

};