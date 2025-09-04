#pragma once

namespace SClick::Core::Window
{
	struct WindowSettings
	{
		unsigned int width;
		unsigned int hieght;
		int aspectRatio;

		bool isResizable;
		bool hasTitleBar;
	};
}