#include "Application.h"
#include "Log.h"

#include <functional>

#include "Havoc/Events/ApplicationEvent.h"
#include "Havoc/Events/KeyEvent.h"
#include "Havoc/Renderer/RenderCommand.h"
#include "Havoc/Renderer/Renderer.h"

namespace Havoc
{
	Application::Application(const char* appName)
		:m_appName(appName), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_Running = true;
		m_window = Window::Create();
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_VertexArray = VertexArray::Create();

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f, 
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0, 1, 2};

		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		squareVA = VertexArray::Create();

		float squareVertices[] = {
			-0.75f, -0.75f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			 0.75f, -0.75f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.75f,  0.75f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color "}
		};

		squareVB->SetLayout(squareLayout);
		squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 0, 2, 3 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		squareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Shader::Create(vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		blueShader = Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == Key::Left)
		{
			H_CORE_DEBUG("{0}", e.ToString());
			m_Camera.SetPostion(m_Camera.GetPosition() - glm::vec3(m_CameraVel, 0.0f, 0.0f));
		}
		else if (e.GetKeyCode() == Key::Right)
		{
			H_CORE_DEBUG("{0}", e.ToString());
			m_Camera.SetPostion(m_Camera.GetPosition() + glm::vec3(m_CameraVel, 0.0f, 0.0f));
		}
		else if (e.GetKeyCode() == Key::Up)
		{
			H_CORE_DEBUG("{0}", e.ToString());
			m_Camera.SetPostion(m_Camera.GetPosition() + glm::vec3(0.0f, m_CameraVel, 0.0f));
		}
		else if (e.GetKeyCode() == Key::Down)
		{
			H_CORE_DEBUG("{0}", e.ToString());
			m_Camera.SetPostion(m_Camera.GetPosition() - glm::vec3(0.0f, m_CameraVel, 0.0f));
		}
		return true;
	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::ClearColor();

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_Shader, squareVA);
			Renderer::Submit(m_Shader, m_VertexArray);

			Renderer::EndScene();

			m_window->OnUpdate();
		}
	}
}