#pragma once

#include <chrono>

namespace SClick::Core::Utility::Timer
{

	class Timer
	{
	public:
		Timer()
		{}

		void Start()
		{
			start = std::chrono::steady_clock::now();
		}

		std::chrono::duration<double, std::milli> End()
		{
			end = std::chrono::steady_clock::now();

			return end - start;
		}

		std::chrono::duration<double, std::milli> Probe()
		{
			return std::chrono::steady_clock::now() - start;
		}

	private:
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
	};
}
