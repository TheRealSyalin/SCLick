#include "pch.h"
#include "sclick/window/os/windows/windowswindow.h"


namespace SClick::Core::Window::OSWindow
{
	WindowsWindow::WindowsWindow()
		:m_handle(0), m_width(100), m_height(100)
	{
		m_eventCallback = nullptr;
	}

	WindowsWindow::WindowsWindow(char* p_windowName, unsigned short p_width, unsigned short p_height)
		:m_handle(0), m_width(p_width), m_height(p_height), m_eventCallback(nullptr)
	{
		m_windowName = p_windowName;
	}

	WindowsWindow::~WindowsWindow()
	{
		m_eventCallback = nullptr;
	}

	LRESULT WindowsWindow::ThisWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		assert(m_eventCallback);

		if (uMsg == WM_CLOSE)
		{
			DestroyWindow(hwnd);
			return 0;
		}

		if (uMsg == WM_DESTROY)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::WindowDestroy), 0, 0);

			PostQuitMessage(0);

			return 0;
		}
		if (uMsg == WM_PAINT)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::WindowRedraw), 0, 0);
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		unsigned short x = LOWORD(lParam);
		unsigned short y = HIWORD(lParam);

		if (uMsg == WM_SIZE)
		{
			m_width = x;
			m_height = y;
			m_eventCallback((unsigned int)EventType::WindowResize, x, y);

			return 0;
		}

		if (uMsg == WM_MOVE)
		{
			m_eventCallback((unsigned int)EventType::WindowMove, x, y);
			return 0;
		}

		//bit shift the MouseButton code left by 16 to | it with the event type
		unsigned int LMouseDownCode = MouseButtons::LMOUSEDOWN << 16;
		unsigned int RMouseDownCode = MouseButtons::RMOUSEDOWN << 16;
		unsigned int MMouseDownCode = MouseButtons::MMOUSEDOWN << 16;
		unsigned int LMouseUpCode = MouseButtons::LMOUSEUP << 16;
		unsigned int RMouseUpCode = MouseButtons::RMOUSEUP << 16;
		unsigned int MMouseUpCode = MouseButtons::MMOUSEUP << 16;

		if (uMsg == WM_MOUSEMOVE)
		{
			m_eventCallback((unsigned int)EventType::MouseMove, x, y);
			return 0;
		}

		// LEFT MOUSE BUTTON //
		if (uMsg == WM_LBUTTONDOWN)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::MouseButtonDown) | LMouseDownCode, x, y);
			return 0;
		}

		if (uMsg == WM_LBUTTONUP)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::MouseButtonUp) | LMouseUpCode, x, y);
			return 0;
		}

		// RIGHT MOUSE BUTTON //
		if (uMsg == WM_RBUTTONDOWN)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::MouseButtonDown) | RMouseDownCode, x, y);
			return 0;
		}

		if (uMsg == WM_RBUTTONUP)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::MouseButtonUp) | RMouseUpCode, x, y);
			return 0;
		}

		 // MIDDLE MOUSE BUTTON //
		if (uMsg == WM_MBUTTONDOWN)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::MouseButtonDown) | MMouseDownCode, x, y);
			return 0;
		}

		if (uMsg == WM_MBUTTONUP)
		{
			m_eventCallback(static_cast<unsigned int>(EventType::MouseButtonUp) | MMouseUpCode, x, y);
			return 0;
		}

		/*
		In case of EventType::KeyPress, highWord is the KeyCode to be translated
		lowWord indicates a repeat event. lowWord is just for logging purposes.
		*/
		if (uMsg == WM_KEYDOWN)
		{
			/*
			WinUser.h offers ways to get the repeat bit,
			but i like doing it myself cuz im tired of looking at capital letters.
			*/
			std::uint64_t bitMask = static_cast<std::uint64_t>(1) << 30;
			std::uint64_t bit = bitMask & lParam;

			if (bit != 0)
				m_eventCallback(static_cast<unsigned int>(EventType::KeyRepeat), static_cast<unsigned short>(wParam), 1);
			else
				m_eventCallback(static_cast<unsigned int>(EventType::KeyPress), static_cast<unsigned short>(wParam), 0);

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

		wchar_t windowName[256];
		MultiByteToWideChar(CP_UTF8, 0, m_windowName, -1, windowName, 256);

		m_handle = CreateWindowEx(0,
			CLASSNAME, 
			windowName, 
			WS_OVERLAPPEDWINDOW,
			0, 0, m_width, m_height, 0, 0, 
			hInstance, 
			this);

		ShowWindow(m_handle, SW_SHOWDEFAULT);

		return 0;
	}

	void WindowsWindow::HandleMessages()
	{
		MSG o_msg;

		while (PeekMessageW(&o_msg, m_handle, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&o_msg);
			DispatchMessage(&o_msg);
		}
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
		m_eventCallback = func;
	}
	const unsigned short WindowsWindow::GetWidth()
	{
		return m_width;
	}
	const unsigned short WindowsWindow::GetHeight()
	{
		return m_height;
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
}