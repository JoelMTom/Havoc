#include <Havoc.h>

#include <glm/glm.hpp>


class ExampleLayer : public Havoc::Layer
{
public:
	ExampleLayer()
		:Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray = Havoc::VertexArray::Create();

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
		};

		m_VertexBuffer = Havoc::VertexBuffer::Create(vertices, sizeof(vertices));
		Havoc::BufferLayout layout = {
			{ Havoc::ShaderDataType::Float3, "a_Position" },
			{ Havoc::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };

		m_IndexBuffer = Havoc::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		squareVA = Havoc::VertexArray::Create();

		float squareVertices[] = {
			-0.75f, -0.75f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
			 0.75f, -0.75f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.75f,  0.75f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
		};

		std::shared_ptr<Havoc::VertexBuffer> squareVB = Havoc::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		Havoc::BufferLayout squareLayout = {
			{ Havoc::ShaderDataType::Float3, "a_Position" },
			{ Havoc::ShaderDataType::Float4, "a_Color "}
		};

		squareVB->SetLayout(squareLayout);
		squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 0, 2, 3 };
		std::shared_ptr<Havoc::IndexBuffer> squareIB = Havoc::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

		m_Shader = Havoc::Shader::Create(vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		blueShader = Havoc::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc);
	}

	void OnUpdate() override
	{
		if (Havoc::Input::IsKeyPressed(Havoc::Key::Left))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if(Havoc::Input::IsKeyPressed(Havoc::Key::Right))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Havoc::Input::IsKeyPressed(Havoc::Key::Up))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Havoc::Input::IsKeyPressed(Havoc::Key::Down))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		Havoc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Havoc::RenderCommand::ClearColor();

		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Havoc::Renderer::BeginScene(m_Camera);

		Havoc::Renderer::Submit(blueShader, squareVA);
		Havoc::Renderer::Submit(m_Shader, m_VertexArray);

		Havoc::Renderer::EndScene();
	}

	void OnEvent(Havoc::Event& e)
	{
		//H_CLIENT_DEBUG("{0}", e.ToString());
	}

private:
	std::shared_ptr<Havoc::VertexArray> m_VertexArray;
	std::shared_ptr<Havoc::VertexArray> squareVA;
	std::shared_ptr<Havoc::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Havoc::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Havoc::Shader> m_Shader;
	std::shared_ptr<Havoc::Shader> blueShader;

	Havoc::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.01f;
	float m_CameraRotation = 0.0f;
};

class HavocLand : public Havoc::Application
{

public:

	HavocLand(const char* name)
		:Havoc::Application(name)
	{
		PushLayer(new ExampleLayer());
	}
	
	~HavocLand()
	{

	}
};

Havoc::Application* Havoc::CreateApplication()
{
	return new HavocLand("HavocLand");
}