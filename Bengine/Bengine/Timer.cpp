#include "timer.h"

BG::Timer::Timer()
{
	this->interval_ = 0;
	reset();
}

BG::Timer::Timer(const int& interval)
{
	this->interval_ = interval;
	reset();
}

bool BG::Timer::expired() const
{
	return time() - last_tick_ > interval_;
}

void BG::Timer::reset()
{
	last_tick_ = time();
}

int BG::Timer::time() const
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count());
}
