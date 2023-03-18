#include "Window.h"
#include "Platform/windows/WindowsWindow.h"
//#include "Platform/Windows/Win32.h"

namespace Havoc
{
	std::unique_ptr<Window> Window::Create(const WindowProperties& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}
} 