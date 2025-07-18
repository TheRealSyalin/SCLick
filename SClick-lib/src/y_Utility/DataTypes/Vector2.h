#pragma once


namespace SClick::Core::Utility
{
	struct Vector2
	{
	public:
		double x;
		double y;

	public:
		Vector2(double p_x, double p_y) : x(p_x), y(p_y) {}

		Vector2 operator=(Vector2 other)
		{
			x = other.x;
			y = other.y;
		}

		Vector2 operator*(Vector2 other)
		{
			x *= other.x;
			y *= other.y;
		}

		void SetX(double p_x)
		{
			x = p_x;
		}

		void SetY(double p_y)
		{
			y = p_y;
		}
	};
}