#include "Win32.h"
#include "fmt/format.h"

#include <windows.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		H_CORE_DEBUG("{} key Pressed!", (char)wParam);
		break;
	case WM_MOUSEMOVE: {
		int x_position = GET_X_LPARAM(lParam);
		int y_position = GET_Y_LPARAM(lParam);

		H_CORE_DEBUG("Mouse Moved: x - {0}, y - {1}", x_position, y_position);
	} break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


namespace Havoc
{
	Win32::Win32(const WindowProperties& props)
	{
		m_data.title = props.m_title;
		m_data.width = props.m_width;
		m_data.height = props.m_height;
		Init(props);
	}

	Win32::~Win32()
	{
		shutdown();
	}

	void Win32::Init(const WindowProperties& props)
	{

		WNDCLASSA wc = { };
		wc.lpfnWndProc = WindowProc;
		wc.style = CS_DBLCLKS;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hInstance = GetModuleHandleA(NULL);
		wc.lpszClassName = "Havoc Engine";

		if (!RegisterClassA(&wc))
		{
			MessageBox(NULL, "Window Registration Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			H_CORE_FATAL("Window Registration Failed!");
			return;
		}

		H_CORE_DEBUG("Window Registered");

		uint32_t window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		uint32_t window_ex_style = WS_EX_APPWINDOW;
		window_style |= WS_MAXIMIZEBOX;
		window_style |= WS_MINIMIZEBOX;
		window_style |= WS_THICKFRAME;

		HWND hwnd = CreateWindowExA(
			window_ex_style,
			"Havoc Engine",
			props.m_title,
			window_style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			props.m_width,
			props.m_height,
			NULL,
			NULL,
			wc.hInstance,
			NULL
		);

		if (hwnd == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			//H_CORE_FATAL("Window Creation Failed!");
			return;
		}

		H_CORE_DEBUG("Window Created");

		ShowWindow(hwnd, SW_SHOW);

	}

	void Win32::OnUpdate()
	{
		MSG Msg;

		while (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	void Win32::shutdown()
	{

	}
}
