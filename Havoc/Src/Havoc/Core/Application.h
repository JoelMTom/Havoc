#pragma once

#include <string>
#include <memory>

#include "Window.h"
#include "Havoc/Events/Event.h"
#include "Havoc/Renderer/Buffer.h"
#include "Havoc/Renderer/Shader.h"
#include "Havoc/Renderer/VertexArray.h"

namespace Havoc
{
	class Application
	{
	public:
		Application(const char*);
		~Application();

		void Run();
		void OnEvent(Event& e);

		bool OnWindowClose(Event& e);
		//bool OnKeyPressed(Event& e);

	private:
		std::string m_appName;
		bool m_Running;
		std::unique_ptr<Window> m_window;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> squareVA;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> blueShader;
	};

	Application* CreateApplication();
}