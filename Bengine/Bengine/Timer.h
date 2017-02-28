#pragma once
#include <chrono>

namespace BG
{
	class Timer
	{

	public:

		Timer();
		explicit Timer(const int &interval);

		bool expired() const;
		void reset();

	private:

		int interval_;
		int last_tick_;

		int time() const;

	};

	typedef std::chrono::time_point<std::chrono::steady_clock> Time;
	typedef std::chrono::high_resolution_clock Clock;

}

