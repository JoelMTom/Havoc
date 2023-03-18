#pragma once

#include <string>

#include "Window.h"

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
		std::unique_ptr<Window> m_window;

		uint32_t m_VertexArray;
		uint32_t m_VertexBuffer;
		uint32_t m_IndexBuffer;
	};

	Application* CreateApplication();
}