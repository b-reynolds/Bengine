#pragma once

namespace BG
{
	
	/**
	 * \brief Basic Colour class containing predefined static colours
	 */
	struct Colour
	{

		Uint8 r_;
		Uint8 g_;
		Uint8 b_;
		Uint8 a_;

		Colour() : r_(0), g_(0), b_(0), a_(0) {}
		Colour(const Uint8 &r, const Uint8 &g, const Uint8 &b) : r_(r), g_(g), b_(b), a_(255) {}
		Colour(const Uint8 &r, const Uint8 &g, const Uint8 &b, const Uint8 &a) : r_(r), g_(g), b_(b), a_(a) {}

	};

	static const Colour kClrBlack = Colour(0, 0, 0, 255);
	static const Colour kClrWhite = Colour(255, 255, 255, 255);

	static const Colour kClrRed = Colour(255, 0, 0, 255);
	static const Colour kClrGreen = Colour(0, 255, 0, 255);
	static const Colour kClrblue = Colour(0, 0, 255, 255);

	static const Colour kClrPink = Colour(255, 51, 255, 255);

}

