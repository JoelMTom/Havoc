#include "Application.h"
#include "Log.h"

#include <functional>

namespace Havoc
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const char* appName)
		:m_appName(appName)
	{
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		//dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	//bool Application::OnKeyPressed(KeyPressedEvent& e)
	//{
	//	if (e.GetKeyCode() == Key::Left)
	//	{
	//		m_Camera.SetPostion(m_Camera.GetPosition() - glm::vec3(m_CameraVel, 0.0f, 0.0f));
	//	}
	//	else if (e.GetKeyCode() == Key::Right)
	//	{
	//		m_Camera.SetPostion(m_Camera.GetPosition() + glm::vec3(m_CameraVel, 0.0f, 0.0f));
	//	}
	//	else if (e.GetKeyCode() == Key::Up)
	//	{
	//		m_Camera.SetPostion(m_Camera.GetPosition() + glm::vec3(0.0f, m_CameraVel, 0.0f));
	//	}
	//	else if (e.GetKeyCode() == Key::Down)
	//	{
	//		m_Camera.SetPostion(m_Camera.GetPosition() - glm::vec3(0.0f, m_CameraVel, 0.0f));
	//	}
	//	return false;
	//}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
}