#pragma once

#include <string>
#include <memory>

#include "Window.h"
#include "Havoc/Events/Event.h"
#include "Havoc/Renderer/Buffer.h"
#include "Havoc/Renderer/Shader.h"

namespace Havoc
{
	class Application
	{
	public:
		Application(const char*);
		~Application();

		void Run();
		void OnEvent(Event& e);

		bool Application::OnWindowClose(Event& e);

	private:
		std::string m_appName;
		bool m_Running;
		std::unique_ptr<Window> m_window;

		uint32_t m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	Application* CreateApplication();
}