#pragma once

#include <string>
#include <memory>

#include "Window.h"
#include "Havoc/Events/Event.h"
#include "Havoc/Events/KeyEvent.h"
#include "Havoc/Events/ApplicationEvent.h"
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
		//bool OnKeyPressed(KeyPressedEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }

	private:
		std::string m_appName;
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}