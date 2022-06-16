#pragma once

#include <string>

namespace Havoc
{
	class Application
	{
	public:
		Application(const char*);
		~Application();
		void Run();

	private:
		std::string m_appName;
		bool m_runnning;
	};

	Application* CreateApplication();
}