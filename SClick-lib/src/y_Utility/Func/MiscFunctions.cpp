#include "pch.h"
#include "MiscFunctions.h"

namespace SClick::Core::Utility
{
	std::uint64_t GenerateUUID64()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto epoch = now.time_since_epoch();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(epoch);
		std::uint64_t time = static_cast<std::uint64_t>(duration.count());

		time = time | time * time * time;
		unsigned short chunks[4] = {
			static_cast<unsigned short>(time),
			static_cast<unsigned short>(time >> 16),
			static_cast<unsigned short>(time >> 32),
			static_cast<unsigned short>(time >> 48) };

		auto mod = chunks[0] % chunks[1];
		if (mod == 0) mod = 1;
		chunks[2] *= chunks[3] / mod;

		std::uint64_t d =
			(std::uint64_t)chunks[0]
			| (std::uint64_t)chunks[1] << 16
			| (std::uint64_t)chunks[2] << 32
			| (std::uint64_t)chunks[3] << 48;

		return d;
	}
	std::uint32_t GenerateUUID32()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto epoch = now.time_since_epoch();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(epoch);
		std::uint32_t time = static_cast<std::uint32_t>(duration.count());

		time = time | time * time * time;

		return time;
	}
}