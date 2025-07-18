#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include "Core.h"

namespace SClick::Application
{
	inline void Run(Core::Window::Window& window, SClick::Core::Renderer::Renderer renderer, Core::EventSystem::EventManager& mainWindowEventManager)
	{
		bool isRunning = true;

		double lastTime = 0;
		double accumulateOneSecond = 0;

		Core::Utility::Timer::Timer timer;
		Core::Utility::Timer::Timer eventTimer;

		//------------Create UI------------//
		
		Core::Renderer::Control::Control control = { Core::Utility::Rect(100, 100, 0, 0), Core::Utility::Color(1, 1, 1),
			mainWindowEventManager};

		Core::Renderer::Control::Control buttonControl = { &control, Core::Utility::Rect(0, 0, 300, 300), Core::Utility::Color(1, 1, 1),
			mainWindowEventManager};

		//Core::Renderer::Layer::Layer GUILayer = new Layer();
		//Core::Renderer::Layer::Layer CanvasLayer = new Layer();

		//GUILayer.push(buttonControl);

		//------------Create UI------------//

		while (isRunning)
		{
			timer.Start();
			const double delta = (lastTime - timer.Probe().count()) / 1000;
			accumulateOneSecond += delta;

			if (accumulateOneSecond >= 1)
			{
				//std::cout << "\r" << "FPS: " << (int)(1 / delta) << " ";
				accumulateOneSecond = 0;
			}

			window.Update();

			//eventTimer.Start();
			//------------Event Loop------------//
			while (!mainWindowEventManager.GetEventCollector().GetEventQueue().IsEmpty())
			{
				buttonControl.OnClick(MouseButtons::LMOUSE, true);
				buttonControl.OnClick(MouseButtons::RMOUSE, true);
				buttonControl.OnClick(MouseButtons::MMOUSE, true);
				buttonControl.OnHover();



				mainWindowEventManager.HandleEvent(EventType::WindowRedraw, [](unsigned short _1, unsigned short _2)
					{
						//renderer.Clear();

						//renderer.Draw(CanvasLayer);
						//renderer.Draw(GUILayer);
						
						//renderer.Display();

						std::cout << "PAINT" << std::endl;
						return true;
					});

				mainWindowEventManager.HandleEvent(EventType::WindowResize, [](unsigned short _1, unsigned short _2)
					{
						std::cout << _1 << ", " << _2 << std::endl;
						return true;
					});

				mainWindowEventManager.HandleEvent(EventType::WindowDestroy, [&isRunning](unsigned short _1, unsigned short _2)
					{
						std::cout << "Quit" << std::endl;
						isRunning = false;
						return true;
					});

				mainWindowEventManager.HandleEvent(EventType::MouseMove, [](unsigned short _1, unsigned short _2)
					{
						std::cout << _1 << ", " << _2 << " 1" << std::endl;
						return true;
					});

				mainWindowEventManager.HandleEvent(EventType::KeyPress, [](unsigned short _1, unsigned short _2)
					{
						std::cout << (char)_1 << std::endl;
						if (_1 == KeyCodes::ENTER)
							std::cout << "\n";

						return true;
					});

				mainWindowEventManager.HandleEvent(EventType::KeyRepeat, [](unsigned short _1, unsigned short _2)
					{
						std::cout << (char)_1 << " " << _2;
						if (_1 == KeyCodes::ENTER)
							std::cout << "\n";

						return true;
					});

				mainWindowEventManager.GetEventCollector().GetEventQueue().Dequeue();
			}
			//std::cout << eventTimer.End().count() << std::endl;

			{
				using namespace std::chrono_literals;

				unsigned long long sleepTime = (unsigned long long)16 - (unsigned long long)delta;
				//std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
			}


			//std::cout << timer.End().count() << std::endl;
			lastTime = timer.End().count();
		} 
	}
}
