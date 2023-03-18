#pragma once

#include <string>
#include <memory>

#include "Window.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

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
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	Application* CreateApplication();
}