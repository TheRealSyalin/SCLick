#include "pch.h"
#include "Rect.h"

namespace SClick::Core::DataType
{
	Rect::Rect(std::uint16_t p_xPos, std::uint16_t p_yPos, std::uint16_t p_width, std::uint16_t p_height) : xPos(p_xPos), yPos(p_yPos), width(p_width), height(p_height)
	{
	}
	Rect::Rect() : xPos(0), yPos(0), width(0), height(0)
	{
	}
}