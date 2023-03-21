#include "WindowsWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Havoc/Core/Log.h"
#include "Havoc/Events/ApplicationEvent.h"

namespace Havoc
{
	static uint8_t s_GLFWwindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		H_CORE_ERROR("GLFW Error: ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.EventCallback = nullptr;
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init()
	{

		H_CORE_INFO("Creating Window: {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (s_GLFWwindowCount == 0)
		{
			if (!glfwInit())
			{
				H_CORE_ERROR("Could not inititalize GLFW!");
				__debugbreak();
			}
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		++s_GLFWwindowCount;

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		delete m_Context;
	}

	void WindowsWindow::SetVSync(bool Vsync)
	{
		if (Vsync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.Vsync;
	}
}