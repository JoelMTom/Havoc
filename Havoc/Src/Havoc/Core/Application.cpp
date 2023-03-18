#include "Application.h"
#include "Log.h"

namespace Havoc
{
	Application::Application(const char* appName)
		:m_appName(appName)
	{
		m_runnning = true;
		m_window = Window::Create();
		/*H_CORE_FATAL("Havoc Engine {0}", "hello!");
		H_CORE_ERROR("Havoc Engine {0}", "hello!");
		H_CORE_WARN("Havoc Engine {0}", "hello!");
		H_CORE_DEBUG("Havoc Engine {0}", "hello!");
		H_CORE_INFO("Havoc Engine {0}", "hello!");
		H_CORE_TRACE("Havoc Engine {0}\n\n", "hello!");



		H_CLIENT_FATAL("Havoc Engine {0}", "hello!");
		H_CLIENT_ERROR("Havoc Engine {0}", "hello!");
		H_CLIENT_WARN("Havoc Engine {0}", "hello!");
		H_CLIENT_DEBUG("Havoc Engine {0}", "hello!");
		H_CLIENT_INFO("Havoc Engine {0}", "hello!");
		H_CLIENT_TRACE("Havoc Engine {0}", "hello!");*/
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_runnning)
		{
			m_window->OnUpdate();
		}
	}
}