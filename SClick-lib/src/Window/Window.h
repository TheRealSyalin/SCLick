#pragma once

#ifdef WINDOWS
#include "OS/Windows/WindowsWindow.h"
#define SCLICKWINDOW SClick::Core::Window::OSWindow::WindowsWindow
#endif

#ifdef LINUX
#include "OS/Linux/LinuxWindow.h"
#define SCLICKWINDOW SClick::Core::Window::OSWindow::LinuxWindow
#endif

#include <functional>
#include <tuple>

namespace SClick::Core::Window
{
	class Window
	{
	public:
		Window(char* p_windowName, unsigned int p_width, unsigned int p_hieght, 
			std::function<void(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)> p_eventHandlerCallback);

		~Window();

	public:
		int Update();
		void CleanUp();

	public:
		std::pair<unsigned int, unsigned int> GetSize();
		void* GetWindowHandle();
		void SetParentWindow(void* p_parent);

	public:
		Window& operator=(Window&& other) noexcept;

	private:
		SCLICKWINDOW* window;
	};
}
