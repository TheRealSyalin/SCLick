#include "pch.h"
#include "color.h"

namespace SClick::Core::DataType
{
	Color::Color(unsigned char p_r, unsigned char p_g, unsigned char p_b, unsigned char p_a) : r(p_r), g(p_g), b(p_b), a(p_a)
	{
	}
	Color::Color() : r(255), g(32), b(155), a(255)
	{
	}
}