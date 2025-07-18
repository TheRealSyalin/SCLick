#include "Application/Application.h"


int main()
{
	SClick::Core::Renderer::Renderer renderer;
	SClick::Core::EventSystem::EventManager mainWindowEventManager;
	SClick::Core::Window::Window window = { "SClick", 1920, 1080, mainWindowEventManager };

	SClick::Application::Run(window, renderer ,mainWindowEventManager);
}