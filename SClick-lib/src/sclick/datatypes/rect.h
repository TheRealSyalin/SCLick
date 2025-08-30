#pragma once


namespace SClick::Core::DataType
{
	struct Rect
	{
	public:
		Rect(std::uint16_t p_xPos, std::uint16_t p_yPos, std::uint16_t p_width, std::uint16_t p_height);
		Rect();

	public:
		std::uint16_t xPos, yPos;
		std::uint16_t width, height;
	};
}