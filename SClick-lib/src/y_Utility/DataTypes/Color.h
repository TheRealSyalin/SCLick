#pragma once

namespace SClick::Core::Utility
{
	struct Color
	{
	public:
		Color(float p_r, float p_g, float p_b) : r(p_r), g(p_g), b(p_b)
		{}
		float r, g, b;
	};
}