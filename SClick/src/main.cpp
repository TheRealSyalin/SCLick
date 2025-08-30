#include <cassert>

#include "application\application.h"

int main()
{
	using namespace SClick;

	Core::EventSystem::EventManager windowEventManager;
	Core::Window::Window window = { "SClick", 1920, 1080, windowEventManager.GetEventCallback()};

	Core::Renderer::SCRender_Init(window.GetWindowHandle());
	if (Core::Renderer::SCRender_GetStatus() != 0)
		return 420;
	Application::Run(window, windowEventManager);
	Core::Renderer::SCRender_Shutdown();
}