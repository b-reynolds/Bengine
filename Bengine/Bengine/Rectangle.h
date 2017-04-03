#pragma once
#include "vector2.h"

namespace BG
{
	template <typename T>
	struct Rectangle
	{

		T left_;
		T top_;
		T width_;
		T height_;

		Rectangle() : left_(0), top_(0), width_(0), height_(0) {}
		Rectangle(const T &left, const T &top, const T &width, const T &height) : left_(left), top_(top), width_(width), height_(height) {}
		Rectangle(const Vector2<T> &position, const Vector2<T> &size) : left_(position.x_), top_(position.y_), width_(size.x_), height_(size.y_) {}

		bool intersects(const Rectangle<T> &other);

	};

	template <typename T>
	bool Rectangle<T>::intersects(const Rectangle<T>& other)
	{
		return (left_ < (other.left_ + other.width_) && (left_ + width_) > other.left_ && top_ < (other.top_ + other.height_) && (top_ + height_) > other.top_);
	}

	typedef Rectangle<float> FloatRect;
	typedef Rectangle<int> IntRect;
	typedef Rectangle<unsigned int> UIntRect;

}