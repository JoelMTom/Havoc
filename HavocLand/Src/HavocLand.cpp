#include <Havoc.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "Platform/OpenGL/OpenGLShader.h"


class ExampleLayer : public Havoc::Layer
{
public:
	ExampleLayer()
		:Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
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
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Havoc::VertexBuffer> squareVB = Havoc::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		Havoc::BufferLayout squareLayout = {
			{ Havoc::ShaderDataType::Float3, "a_Position" },
			{ Havoc::ShaderDataType::Float2, "a_TexCoord"}
		};

		squareVB->SetLayout(squareLayout);
		squareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 0, 2, 3 };
		std::shared_ptr<Havoc::IndexBuffer> squareIB = Havoc::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		squareVA->SetIndexBuffer(squareIB);

		m_Shader = Havoc::Shader::Create("assets/Shaders/vertexShader.glsl");
		blueShader = Havoc::Shader::Create("assets/shaders/blueShader.glsl");

		m_Texture = Havoc::Texture2D::Create("assets/textures/checkerboard.png");
		/*m_TTexture = Havoc::Texture2D::Create("assets/textures/tt.png");

		blueShader->Bind();
		blueShader->UploadUniformInt("u_Texture", 0);*/
	}

	void OnUpdate(Havoc::Timestep ts) override
	{
		if (Havoc::Input::IsKeyPressed(Havoc::Key::Left))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if(Havoc::Input::IsKeyPressed(Havoc::Key::Right))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Havoc::Input::IsKeyPressed(Havoc::Key::Up))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Havoc::Input::IsKeyPressed(Havoc::Key::Down))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Havoc::Input::IsKeyPressed(Havoc::Key::A))
			m_SquarePosition.x -= m_CameraMoveSpeed * ts;
		else if (Havoc::Input::IsKeyPressed(Havoc::Key::D))
			m_SquarePosition.x += m_CameraMoveSpeed * ts;

		if (Havoc::Input::IsKeyPressed(Havoc::Key::W))
			m_SquarePosition.y += m_CameraMoveSpeed * ts;
		else if (Havoc::Input::IsKeyPressed(Havoc::Key::S))
			m_SquarePosition.y -= m_CameraMoveSpeed * ts;

		Havoc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Havoc::RenderCommand::ClearColor();



		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Havoc::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

		m_Texture->Bind();
		Havoc::Renderer::Submit(blueShader, squareVA, transform);
		/*m_TTexture->Bind();
		Havoc::Renderer::Submit(blueShader, squareVA, transform1);*/
		Havoc::Renderer::Submit(m_Shader, m_VertexArray);

		Havoc::Renderer::EndScene();
	}

	void OnEvent(Havoc::Event& e)
	{
		
	}

private:
	std::shared_ptr<Havoc::VertexArray> m_VertexArray;
	std::shared_ptr<Havoc::VertexArray> squareVA;
	std::shared_ptr<Havoc::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Havoc::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Havoc::Shader> m_Shader;
	std::shared_ptr<Havoc::Shader> blueShader;
	std::shared_ptr<Havoc::Texture2D> m_Texture;
	std::shared_ptr<Havoc::Texture2D> m_TTexture;

	Havoc::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_SquarePosition;
	float m_CameraMoveSpeed = 5.0f;
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