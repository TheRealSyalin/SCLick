#include "pch.h"
#include "Vector2.h"

namespace SClick::Core::DataType
{
	Vector2::Vector2(double p_x, double p_y) : x(p_x), y(p_y) {}

	Vector2 Vector2::operator=(Vector2& other)
	{
		x = other.x;
		y = other.y;

		return { x, y };
	}

	Vector2 Vector2::operator*(Vector2& other)
	{
		x *= other.x;
		y *= other.y;

		return { x, y };
	}
}