#include <cassert>

#include "application.h"

int main()
{
	using namespace SClick;

	Core::Window::WindowSettings settings = { 0 };
	settings.width = 720;
	settings.hieght = 480;
	settings.aspectRatio = 16 / 9;
	settings.hasTitleBar = true;
	settings.isResizable = false;
	Core::Window::Window window = { "SClick", settings};
	Core::EventSystem::EventManager windowEventManager;

	window.SetEventCallback(windowEventManager.GetEventCallback());

	Core::Renderer::SCRender_Init(window.GetWindowHandle());
	if (Core::Renderer::SCRender_GetStatus() != 0)
		return 420;
	Application::Run(window, windowEventManager);
	Core::Renderer::SCRender_Shutdown();
}