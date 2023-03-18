#pragma once

#include <string>

#include "Havoc/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Havoc
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual void SetVSync(bool vsync);

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool Vsync;
		};

		WindowData m_Data;
	};
}