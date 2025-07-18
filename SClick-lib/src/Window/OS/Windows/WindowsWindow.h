#pragma once

#include <Windows.h>

#include "../I_OSWindow.h"
#include "../../../EventSystem/EventSystem.h"

namespace SClick::Core::Window::OSWindow
{

	class WindowsWindow : public I_OSWindow
	{
	
	public:
		WindowsWindow();
		WindowsWindow(char* p_windowName, unsigned int p_width, unsigned int p_height);
		~WindowsWindow();

	public:
		int SCreateWindow() override;
		void HandleMessages() override;
		void* GetWindowHandle() override;
		void SetParentWindow(void* p_parent) override;
		void SetEventCallback(std::function<void(
			unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)> func) override;

	public:
		LRESULT ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_handle;

	private:
		static LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}