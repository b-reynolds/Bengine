#pragma once
#include "Vector2.h"

namespace BG
{
	template <typename T>
	struct Rectangle
	{

		T left;
		T top;
		T width;
		T height;

		Rectangle() : left(0), top(0), width(0), height(0) {}
		Rectangle(const T &left, const T &top, const T &width, const T &height) : left(left), top(top), width(width), height(height) {}
		Rectangle(const Vector2<T> &position, const Vector2<T> &size) : left(position.x), top(position.y), width(size.x), height(size.y) {}

	};
	
	typedef Rectangle<float> FloatRect;
	typedef Rectangle<int> IntRect;
	typedef Rectangle<unsigned int> UIntRect;

}