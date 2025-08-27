#pragma once

#include <Windows.h>

#include "../../../EventSystem/EventSystem.h"

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
		short m_width, m_height;
	
	public:
		WindowsWindow();
		WindowsWindow(char* p_windowName, unsigned short p_width, unsigned short p_height);
		~WindowsWindow();

	public:
		int SCreateWindow();
		void HandleMessages();
		void* GetWindowHandle();
		void SetParentWindow(void* p_parent);
		void SetEventCallback(std::function<void(
			unsigned int bigWord,
			unsigned short smallWord1,
			unsigned short smallWord2)> func);
		const unsigned short GetWidth();
		const unsigned short GetHeight();

	public:
		LRESULT ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	
	private:
		static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}