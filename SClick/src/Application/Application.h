#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include "SClickCore.h"
#include "Gui.h"

#define TIMERS 0

//TODO: Replace cout with logging system that isnt slow as balls
#if TIMERS
static SClick::Core::Utility::Debug::Timer eventTimer;

#define START_EVENT_TIMER eventTimer.Start();
#define END_EVENT_TIMER std::cout << eventTimer.End().count() << "\n";
#else
#define START_EVENT_TIMER
#define END_EVENT_TIMER 
#endif

namespace SClick::Application
{
	void Run(Core::Window::Window& window, Core::EventSystem::EventManager& windowEventManager)
	{
		bool isRunning = true;

		double lastTime = 0;
		double accumulate = 0;

		unsigned char shift = 1;
		double t = 0;

		Core::Utility::Debug::Timer timer;

		//------------Create UI------------//

		std::vector<SClick::Core::Renderer::Texture> textures;

		while (isRunning)
		{
			START_EVENT_TIMER

			timer.Start();
			const double delta = (lastTime - timer.Probe().count());

			accumulate += delta;


			window.Update();

			//------------Event Loop------------//
			while (!windowEventManager.GetEventQueue().IsEmpty())
			{
				//-----GLOBAL EVENTS-----//

				windowEventManager.HandleEvent(EventType::WindowRedraw, [&textures](unsigned short _1, unsigned short _2)
					{
						std::cout << "PAINT\n";
						return true;
					});

				windowEventManager.HandleEvent(EventType::WindowResize, [](unsigned short _1, unsigned short _2)
					{
						//std::cout << _1 << ", " << _2 << std::endl;
						return true;
					});

				windowEventManager.HandleEvent(EventType::WindowDestroy, [&isRunning](unsigned short _1, unsigned short _2)
					{
						std::cout << "Quit" << std::endl;
						isRunning = false;
						return true;
					});

				windowEventManager.PassthroughEvent(EventType::MouseMove, [](unsigned short _1, unsigned short _2)
					{
						std::cout << _1 << ", " << _2 << " 1" << std::endl;
					});

				windowEventManager.HandleEvent(EventType::KeyPress, [](unsigned short _1, unsigned short _2)
					{
						//std::cout << (char)_1 << std::endl;
						return true;
					});


				//-----APPLICATION EVENTS-----//

				windowEventManager.GetEventQueue().Dequeue();
			}



				//-----GFX-----//
			if (accumulate > 6.94)
			{
				Core::Renderer::SCRender_BeginDraw();

				Core::Renderer::SCRender_ClearFrame();

				Core::Renderer::SCRender_DrawRect({ 0,0,500,500 }, { 255,0,0, 255 });

				Core::Renderer::SCRender_EndDraw();

				Core::Renderer::SCRender_PresentFrame();

				accumulate = 0;
			}

			//git std::this_thread::sleep_for(std::chrono::milliseconds(1));
			lastTime = timer.End().count();
			END_EVENT_TIMER
		}
	}
}
