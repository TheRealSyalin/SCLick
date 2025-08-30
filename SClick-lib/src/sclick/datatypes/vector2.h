#pragma once


namespace SClick::Core::DataType
{
	struct Vector2
	{
	public:
		double x;
		double y;

	public:
		Vector2(double p_x, double p_y);

		Vector2 operator=(Vector2& other);

		Vector2 operator*(Vector2& other);
	};
}