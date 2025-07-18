#pragma once


namespace SClick::Core::Utility
{
	struct Rect
	{
	public:
		Rect(int p_xPos, int p_yPos, int p_width, int p_height) : xPos(p_xPos), yPos(p_yPos), width(p_width), height(p_height) 
		{
			top = yPos;
			bottom = top + height;
			left = xPos;
			right = left + width;
		}

	public:
		int xPos, yPos, width, height;
		int top, bottom, left, right;
	};
}