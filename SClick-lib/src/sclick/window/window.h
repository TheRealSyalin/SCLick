#pragma once

#ifdef WINDOWS
#include "os/windows/windowswindow.h"
#define SCLICKWINDOW SClick::Core::Window::OSWindow::WindowsWindow
#endif

#ifdef LINUX
#include "os/linux/linuxwindow.h"
#define SCLICKWINDOW SClick::Core::Window::OSWindow::LinuxWindow
#endif

#include <functional>
#include <tuple>

#include "sclick\window\windowsettings.h"

namespace SClick::Core::Window
{
	class Window
	{
	private:
		SCLICKWINDOW window;

	public:
		Window(
			char* p_windowName,
			WindowSettings settings);
		~Window();

	public:
		int Update();
		void CleanUp();

	public:
		std::pair<unsigned int, unsigned int> GetSize();
		void* GetWindowHandle();
		void SetEventCallback(std::function<void(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)>& p_eventHandlerCallback);
		void SetParentWindow(void* p_parent);

	public:
		Window& operator=(Window&& other) noexcept;
	};
}


