#pragma once

#include "../Window/Window.h"

namespace SClick::Core::UI
{
	class GUIFactory
	{
	public:
		GUIFactory(Window::Window& p_window) : m_window(p_window)
		{}


	private:
		Window::Window& m_window;
	};
}