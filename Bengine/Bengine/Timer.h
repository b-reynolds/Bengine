#pragma once
#include <chrono>

namespace BG
{
	class Timer
	{

	public:

		Timer();
		explicit Timer(const int &interval);

		bool hasExpired() const;
		void reset();

	private:

		int interval;
		int lastTick;

		int getTime() const;

	};

	typedef std::chrono::time_point<std::chrono::steady_clock> Time;
	typedef std::chrono::high_resolution_clock Clock;

}

