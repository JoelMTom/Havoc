#include "OpenGLContext.h"

#include "Havoc/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Havoc
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_WindowHandle(window)
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			H_CORE_ERROR("Could not load glad!");
		}

		H_CORE_INFO("OpenGL Info:");
		H_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		H_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
		H_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}