#pragma once

#include <Windows.h>
#include <functional>

#include "sclick/eventsystem/src/eventtypes.h"
#include "sclick\window\windowsettings.h"


namespace SClick::Core::Window::OSWindow
{


	class WindowsWindow
	{

	private:
		HWND m_handle;
		std::function<void(
			unsigned int bigWord,
			unsigned short smallWord1,
			unsigned short smallWord2)> m_eventCallback;
		char* m_windowName = "Fuck";
		SClick::Core::Window::WindowSettings m_settings;

	public:
		WindowsWindow();
		WindowsWindow(char* p_windowName, SClick::Core::Window::WindowSettings p_settings);
		~WindowsWindow();

	public:
		int SCreateWindow();
		void HandleMessages();
		void* GetWindowHandle();
		void SetParentWindow(void* p_parent);
		void SetEventCallback(std::function<void(
			unsigned int bigWord,
			unsigned short smallWord1,
			unsigned short smallWord2)>& func);
		const unsigned short GetWidth();
		const unsigned short GetHeight();

	public:
		LRESULT ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	
	private:
		static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}