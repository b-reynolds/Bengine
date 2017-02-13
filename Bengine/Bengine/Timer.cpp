#include "Timer.h"

BG::Timer::Timer()
{
	this->interval = 0;
	reset();
}

BG::Timer::Timer(const int& interval)
{
	this->interval = interval;
	reset();
}

bool BG::Timer::hasExpired() const
{
	return getTime() - lastTick > interval;
}

void BG::Timer::reset()
{
	lastTick = getTime();
}

int BG::Timer::getTime() const
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count());
}
