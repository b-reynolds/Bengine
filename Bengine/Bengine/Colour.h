#pragma once

namespace BG
{
	struct Colour
	{

		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;

		Colour() : r(0), g(0), b(0), a(0) {}
		Colour(const Uint8 &r, const Uint8 &g, const Uint8 &b) : r(r), g(g), b(b), a(255) {}
		Colour(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a) : r(r), g(g), b(b), a(a) {}

	};

	static const Colour CLR_BLACK = Colour(0, 0, 0, 255);
	static const Colour CLR_WHITE = Colour(255, 255, 255, 255);

	static const Colour CLR_RED = Colour(255, 0, 255, 255);
	static const Colour CLR_GREEN = Colour(0, 255, 0, 255);
	static const Colour CLR_BLUE = Colour(0, 0, 255, 255);

	static const Colour CLR_PINK = Colour(255, 51, 255, 255);

}

