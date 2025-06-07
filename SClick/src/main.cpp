#include "pch.h"
#include "Application/Application.h"

int main()
{
	SClick::Core::Window::Window window;
	SClick::Core::EventSystem::EventManager eventManager;

	SClick::Application::Init(window, eventManager);
	SClick::Application::Run(window, eventManager);
	SClick::Application::Shutdown(window, eventManager);
}