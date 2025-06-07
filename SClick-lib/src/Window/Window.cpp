#include "pch.h"
#include "../EventSystem/EventSystem.h"

#include "Window.h"

namespace SClick::Core::Window
{
	Window::Window()
	{
		window = nullptr;
	}

	Window::Window(char* p_windowName, unsigned int p_width, unsigned int p_hieght, EventSystem::EventManager& manager)
	{
		window = new SCLICKWINDOW(p_windowName, p_width, p_hieght);
		window->SetEventCallback([&manager](unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord) {
			manager.GetEventCollector().CollectorCallback(eventTypeWord, highWord, lowWord);
			});

		window->SCreateWindow();
	}

	Window::~Window()
	{
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

    bool& Window::IsRunning()
    {
        return window->m_isRunning;
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
