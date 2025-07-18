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

	LRESULT WindowsWindow::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		
		if (uMsg == WM_CLOSE)
		{
			DestroyWindow(hwnd);
			return 0;
		}

		if (uMsg == WM_DESTROY)
		{
			m_EventCallback((unsigned int)EventType::WindowDestroy, 0, 0);

			PostQuitMessage(0);

			return 0;
		}

		if (uMsg == WM_PAINT)
		{
			m_EventCallback((unsigned int)EventType::WindowRedraw, 0, 0);
		}

		if (uMsg == WM_SIZE)
		{
			unsigned short width = LOWORD(lParam);
			unsigned short height = HIWORD(lParam);

			m_width = width;
			m_height = height;

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::WindowResize, width, height);

			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		unsigned int LMouseCode = MouseButtons::LMOUSE << 16;
		unsigned int RMouseCode = MouseButtons::RMOUSE << 16;
		unsigned int MMouseCode = MouseButtons::MMOUSE << 16;

		if (uMsg == WM_MOUSEMOVE)
		{

			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseMove, x, y);
		}

		// LEFT MOUSE BUTTON //
		if (uMsg == WM_LBUTTONDOWN)
		{
			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseButtonDown | LMouseCode, x, y);
		}

		if (uMsg == WM_LBUTTONUP)
		{
			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseButtonUp | LMouseCode, x, y);
		}

		// RIGHT MOUSE BUTTON //
		if (uMsg == WM_RBUTTONDOWN)
		{
			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseButtonDown | RMouseCode, x, y);
		}

		if (uMsg == WM_RBUTTONUP)
		{
			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseButtonUp | RMouseCode, x, y);
		}

		 // MIDDLE MOUSE BUTTON //
		if (uMsg == WM_MBUTTONDOWN)
		{
			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseButtonDown | MMouseCode, x, y);
		}

		if (uMsg == WM_MBUTTONUP)
		{
			unsigned short x = LOWORD(lParam);
			unsigned short y = HIWORD(lParam);

			if (m_EventCallback)
				m_EventCallback((unsigned int)EventType::MouseButtonUp | MMouseCode, x, y);
		}

		/*
		In case of EventType::KeyPress, highWord is the KeyCode to be translated
		lowWord indicates a repeat event. This is just for logging purposes.
		*/
		if (uMsg == WM_KEYDOWN)
		{
			/*
			WinUser.h offers ways to get the repeat bit,
			but i like doing it myself cuz im tired of looking at capital letters.
			*/
			unsigned long long bitMask = static_cast<unsigned long long>(1) << 30;
			unsigned long long bit = bitMask & lParam;

			if (bit != 0)
				m_EventCallback((unsigned int)EventType::KeyRepeat, static_cast<unsigned short>(wParam), 1);
			else
				m_EventCallback((unsigned int)EventType::KeyPress, static_cast<unsigned short>(wParam), 0);
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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

		if(window)
			return window->ThisWindowProc(hwnd, uMsg, wParam, lParam);

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