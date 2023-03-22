#include "Application.h"
#include "Log.h"

#include <functional>

#include <glad/glad.h>

#include "Havoc/Events/ApplicationEvent.h"
#include "Havoc/Events/KeyEvent.h"

namespace Havoc
{
	Application::Application(const char* appName)
		:m_appName(appName)
	{
		m_Running = true;
		m_window = Window::Create();
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_VertexArray = VertexArray::Create();

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f, 
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		/*glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*) (3 * sizeof(float)));*/

		uint32_t indices[] = { 0, 1, 2, 0, 2, 3};

		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		//dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));
	}

	bool Application::OnWindowClose(Event& e)
	{
		m_Running = false;
		return true;
	}

	/*bool Application::OnKeyPressed(Event& e)
	{
		H_CORE_DEBUG("{0}", e.ToString());
		return true;
	}*/

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_window->OnUpdate();
		}
	}
}