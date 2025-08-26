#include "pch.h"

#include "../EventSystem/EventSystem.h"
#include "Window.h"

namespace SClick::Core::Window
{
	Window::Window(
		char* p_windowName, 
		unsigned int p_width, 
		unsigned int p_hieght, 
		std::function<void(unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)> p_eventHandlerCallback)
	{
		window = new SCLICKWINDOW(p_windowName, p_width, p_hieght);

		window->SetEventCallback(p_eventHandlerCallback);

		window->SCreateWindow();
	}

	Window::~Window()
	{
		CleanUp();
	}

	int Window::Update()
	{
		window->HandleMessages();

		return 0;
	}

	void Window::CleanUp()
	{
		delete window;
		window = nullptr;
	}

	unsigned int Window::GetWidth()
	{
		return window->GetWidth();
	}

	unsigned int Window::GetHeight()
	{
		return window->GetHeight();
	}

	void* Window::GetWindowHandle()
	{
		return window->GetWindowHandle();
	}

	void Window::SetParentWindow(void* p_parent)
	{
		window->SetParentWindow(p_parent);
	}

    Window& Window::operator=(Window&& other) noexcept
    {
		window = other.window;
		other.window = nullptr;
		return *this;
    }
}
