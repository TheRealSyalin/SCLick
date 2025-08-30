#include "pch.h"

#include "Timer.h"

namespace SClick::Core::Utility::Debug
{
	Timer::Timer(){}

	void Timer::Start()
	{
		start = std::chrono::steady_clock::now();
	}

	std::chrono::duration<double, std::milli> Timer::End()
	{
		end = std::chrono::steady_clock::now();

		return end - start;
	}

	std::chrono::duration<double, std::milli> Timer::Probe()
	{
		return std::chrono::steady_clock::now() - start;
	}

}