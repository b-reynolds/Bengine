#pragma once

namespace BG
{
	/*
	 * \brief Vector2 template Class with operator overloading
	 */
	template<class T>
	struct Vector2
	{

		T x_;
		T y_;

		Vector2() : x_(0), y_(0) {}
		Vector2(const T &x, const T &y) : x_(x), y_(y) {}

		Vector2& operator+(const Vector2 &v) { x_ += v.x_; y_ += v.y_; return *this; }
		Vector2& operator+=(const Vector2 &v) { x_ += v.x_; y_ += v.y_; return *this; }

		Vector2& operator-(const Vector2 &v) { x_ -= v.x_; y_ -= v.y_; return *this; }
		Vector2& operator-=(const Vector2 &v) { x_ -= v.x_; y_ -= v.y_; return *this; }

		Vector2& operator*(const Vector2 &v) { x_ *= v.x_; y_ *= v.y_; return *this; }
		Vector2& operator*=(const Vector2 &v) { x_ *= v.x_; y_ *= v.y_; return *this; }
		Vector2& operator*(const T &scalar) { x_ *= scalar; y_ *= scalar; return *this; }

		Vector2& operator/(const Vector2 &v) { x_ /= v.x_; y_ /= v.y_; return *this; }
		Vector2& operator/=(const Vector2 &v) { x_ /= v.x_; y_ /= v.y_; return *this; }
		Vector2 operator/(const T &scalar) { x_ /= scalar; y_ /= scalar; return *this; }

		bool operator==(const Vector2 &v) { return x_ == v.x_ && y_ == v.y_; }
		bool operator!=(const Vector2 &v) { return !(*this == v); }

	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<double> Vector2d;

}