#pragma once

#include <iostream>
#include <bitset>

#include "pch.h"
#include "Core.h"

namespace SClick::Application
{
	inline int Init(Core::Window::Window& window, Core::EventSystem::EventManager& eventManager)
	{
		window = { "SClick", 1920, 1080, eventManager };

		return 0;
	}

	inline void Shutdown(Core::Window::Window& window, Core::EventSystem::EventManager& eventManager)
	{
		window.CleanUp();
	}

	inline void Run(Core::Window::Window& window, Core::EventSystem::EventManager& eventManager)
	{
		bool isRunning = true;

		while (isRunning)
		{
			window.Update();


			//------------Event Loop------------//
			while (!eventManager.GetEventCollector().GetEventQueue().isEmpty)
			{
				eventManager.PeekEvent(EventType::WindowResize, [](unsigned short _1, unsigned short _2) {
					std::cout << _1 << ", " << _2 << std::endl;
					});


				eventManager.PeekEvent(EventType::WindowDestroy, [&isRunning](unsigned short _1, unsigned short _2) {
					std::cout << "Quit" << std::endl;
					isRunning = false;
					});

				eventManager.PeekEvent(EventType::KeyPress, [](unsigned short _1, unsigned short _2) {

					std::cout << (char)_1;
					if (_1 == KeyCodes::ENTER)
						std::cout << "\n";
					});

				eventManager.PeekEvent(EventType::KeyRepeat, [](unsigned short _1, unsigned short _2) {

					std::cout << (char)_1 << " " << _2;
					if (_1 == KeyCodes::ENTER)
						std::cout << "\n";
					});
			}

		} 
	}
}
