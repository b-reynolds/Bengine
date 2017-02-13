#pragma once

namespace BG
{
	struct Colour
	{

		Uint8 r;
		Uint8 g;
		Uint8 b;

		Colour() : r(0), g(0), b(0) {}
		Colour(const Uint8 &r, const Uint8 &g, const Uint8 &b) : r(r), g(g), b(b) {}

	};
}

