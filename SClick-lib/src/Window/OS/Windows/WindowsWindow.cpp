#include "pch.h"
#include "../Windows/WindowsWindow.h"

namespace SClick::Core::Window::OSWindow
{
	WindowsWindow::WindowsWindow()
		:m_handle(0)
	{
		m_EventCallback = NULL;
	}

	WindowsWindow::WindowsWindow(char* p_windowName, unsigned int p_width, unsigned int p_height)
		:m_handle(0)
	{
		m_windowName = p_windowName;
		m_width = p_width;
		m_height = p_height;
		m_isRunning = true;
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	LRESULT WindowsWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = nullptr;

		auto ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (ptr)
			window = reinterpret_cast<WindowsWindow*>(ptr);


		if (uMsg == WM_CREATE)
		{
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			window = reinterpret_cast<WindowsWindow*>(cs->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		}

		if (uMsg == WM_CLOSE)
		{
			DestroyWindow(hwnd);
			return 0;
		}

		if (uMsg == WM_DESTROY)
		{
			if (window)
				window->m_EventCallback((unsigned int)EventType::WindowDestroy, 0, 0);

			PostQuitMessage(0);

			return 0;
		}

		if (uMsg == WM_SIZE)
		{
			if (!window)
				return 0;

			unsigned short width = LOWORD(lParam);
			unsigned short height = HIWORD(lParam);

			window->m_width = width;
			window->m_height = height;

			if (window->m_EventCallback)
				window->m_EventCallback((unsigned int)EventType::WindowResize, width, height);

			return 0;

		}

		/*
		In case of EventType::KeyPress, highWord is the KeyCode to be translated
		lowWord indicates a repeat event. This is just for logging purposes.
		*/
		if (uMsg == WM_KEYDOWN)
		{
			if (!window)
				return 0;
				/*
				WinUser.h offers ways to get the repeat bit,
				but i like doing it myself cuz im tired of looking at capital letters.
				*/
				unsigned long long bitMask = static_cast<unsigned long long>(1) << 30;
				unsigned long long bit = bitMask & lParam;

				if(bit != 0)
					window->m_EventCallback((unsigned int)EventType::KeyRepeat, static_cast<unsigned short>(wParam), 1);
				else
					window->m_EventCallback((unsigned int)EventType::KeyPress, static_cast<unsigned short>(wParam), 0);

				return 0;

		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	int WindowsWindow::SCreateWindow()
	{
		HINSTANCE hInstance = GetModuleHandle(0);
		const wchar_t CLASSNAME[] = L"SClickWindowClass";

		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.lpszClassName = CLASSNAME;
		wc.hInstance = hInstance;

		RegisterClass(&wc);

		int clen = static_cast<int>(std::strlen(m_windowName)) + 1;
		int wclen = sizeof(char) * clen;
		wchar_t* windowName = new wchar_t[wclen];
		MultiByteToWideChar(CP_UTF8, 0, m_windowName, clen, windowName, wclen);

		m_handle = CreateWindowEx(0,
			CLASSNAME, 
			windowName, 
			WS_OVERLAPPEDWINDOW, 
			0, 0, m_width, m_height, 0, 0, 
			hInstance, 
			this);

		delete[] windowName;
		windowName = nullptr;

		ShowWindow(m_handle, SW_SHOWDEFAULT);

		return 0;
	}

	void WindowsWindow::HandleMessages()
	{
		MSG o_msg;
		PeekMessage(&o_msg, m_handle, 0, 0, PM_REMOVE);
		TranslateMessage(&o_msg);
		DispatchMessage(&o_msg);
	}

	void* WindowsWindow::GetWindowHandle()
	{
		return m_handle;
	}

	void WindowsWindow::SetParentWindow(void* p_parent)
	{
		SetParent(m_handle, reinterpret_cast<HWND>(p_parent));
	}

	void WindowsWindow::SetEventCallback(std::function<void(
		unsigned int eventTypeWord, unsigned short highWord, unsigned short lowWord)> func)
	{
		m_EventCallback = func;
	}
}