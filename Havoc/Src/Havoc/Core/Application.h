#pragma once

#include <string>
#include <memory>

#include "Window.h"
#include "Havoc/Events/Event.h"
#include "Havoc/Events/KeyEvent.h"
#include "Havoc/Events/ApplicationEvent.h"
#include "Havoc/Renderer/Buffer.h"
#include "Havoc/Renderer/Shader.h"
#include "Havoc/Renderer/VertexArray.h"
#include "Havoc/Renderer/OrthographicCamera.h"
#include "Havoc/Core/Layer.h"
#include "Havoc/Core/LayerStack.h"

namespace Havoc
{
	class Application
	{
	public:
		Application(const char*);
		~Application();

		void Run();
		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }

	private:
		std::string m_appName;
		bool m_Running = true;
		std::unique_ptr<Window> m_window;

		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> squareVA;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> blueShader;

		OrthographicCamera m_Camera;

		float m_CameraVel = 0.01f;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}