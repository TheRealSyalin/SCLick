#pragma once

#include <chrono>

namespace SClick::Core::Utility::Debug
{

	class Timer
	{
	public:
		Timer();

		void Start();

		std::chrono::duration<double, std::milli> End();
		std::chrono::duration<double, std::milli> Probe();
	private:
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
	};
}
