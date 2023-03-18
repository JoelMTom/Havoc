#include "WindowsWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Havoc/Core/Log.h"

namespace Havoc
{
	static uint8_t s_GLFWwindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		H_CORE_ERROR("GLFW Error: ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		H_CORE_INFO("Creating Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWwindowCount == 0)
		{
			if (!glfwInit())
			{
				H_CORE_ERROR("Could not inititalize GLFW!");
				__debugbreak();
			}
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title, nullptr, nullptr);
		++s_GLFWwindowCount;

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetVSync(bool Vsync)
	{
		if (Vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}
}