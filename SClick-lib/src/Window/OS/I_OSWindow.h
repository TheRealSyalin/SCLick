#pragma once

#include <functional>

#include "../EventSystem/EventSystem.h"

namespace SClick::Core::Window
{
	 class I_OSWindow
	{
	public:
		 bool m_isRunning = true;
		 
	public:
		virtual int SCreateWindow() = 0;
		virtual void* GetWindowHandle() = 0;
		virtual void SetParentWindow(void* p_parent) = 0;
		virtual void HandleMessages() = 0;
		virtual void SetEventCallback(std::function<void(
			unsigned int bigWord,
			unsigned short smallWord1,
			unsigned short smallWord2)> func) = 0;

	public:
		virtual unsigned int GetWidth() { return m_width; }
		virtual unsigned int GetHeight() { return m_height; }

	protected:

		char* m_windowName = "Fuck";
		unsigned int m_width = 100;
		unsigned int m_height = 100;

		std::function<void(
			unsigned int bigWord,
			unsigned short smallWord1,
			unsigned short smallWord2)> m_EventCallback;
	};
}