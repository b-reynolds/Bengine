#define USE_MATH_DEFINES
#include "math.h"
#include <SDL_stdinc.h>

float BG::Math::radiansToDegrees(const float& radians)
{
	return radians * 180 / M_PI;
}

float BG::Math::degreesToRadians(const float& degrees)
{
	return degrees * M_PI / 180;
}
