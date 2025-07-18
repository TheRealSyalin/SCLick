#pragma once

#ifdef WINDOWS
#include "OS/Windows/WindowsWindow.h"
#define SCLICKWINDOW SClick::Core::Window::OSWindow::WindowsWindow
#endif

#ifdef LINUX
#include "OS/Linux/LinuxWindow.h"
#define SCLICKWINDOW SClick::Core::Window::OSWindow::LinuxWindow
#endif



namespace SClick::Core::Window
{
	class Window
	{
	public:
		Window();
		Window(char* p_windowName, unsigned int p_width, unsigned int p_hieght, EventSystem::EventManager& manager);

		~Window();

	public:
		int Update();
		void CleanUp();

	public:
		unsigned int GetWidth();
		unsigned int GetHeight();
		bool& IsRunning();
		void* GetWindowHandle();
		void SetParentWindow(void* p_parent);

	public:
		Window& operator=(Window&& other) noexcept;

	private:
		SCLICKWINDOW* window;
	};
}
