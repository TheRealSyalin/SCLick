#include "pch.h"

#include "window.h"

namespace SClick::Core::Window
{
	Window::Window(
		char* p_windowName,
		WindowSettings settings)
	{
		window = SCLICKWINDOW(p_windowName, settings);

		window.SCreateWindow();
	}

	Window::~Window()
	{
		CleanUp();
	}

	int Window::Update()
	{
		window.HandleMessages();

		return 0;
	}

	void Window::CleanUp()
	{
	}

	std::pair<unsigned int, unsigned int> Window::GetSize()
	{
		return { window.GetWidth(), window.GetHeight() };
	}

	void* Window::GetWindowHandle()
	{
		return window.GetWindowHandle();
	}

	void Window::SetEventCallback(std::function<void(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)>& p_eventHandlerCallback)
	{
		window.SetEventCallback(p_eventHandlerCallback);
	}

	void Window::SetParentWindow(void* p_parent)
	{
		window.SetParentWindow(p_parent);
	}

    Window& Window::operator=(Window&& other) noexcept
    {
		window = other.window;
		//other.window = nullptr;
		return *this;
    }
}
