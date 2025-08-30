#pragma once

#include <cstdint>

namespace SClick::Core::DataType
{
	struct Color
	{
	public:
		Color(unsigned char p_r, unsigned char p_g, unsigned char p_b, unsigned char p_a);
		Color();
		unsigned char r, g, b, a;
	};
}