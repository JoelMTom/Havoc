#include "Shader.h"
#include "Renderer.h"

#include "Havoc/Core/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Havoc
{

	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("Shader for RendererAPI::None is not supported"); __debugbreak();
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("Shader for RendererAPI::None is not supported"); __debugbreak();
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexsrc, fragmentsrc);
		}

		H_CORE_ERROR("Could initialize shader!");
		__debugbreak();
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		if (Exists(name))
		{
			H_CORE_ERROR("Shader already exists"); __debugbreak();
		}
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
		{
			H_CORE_ERROR("Shader not found"); __debugbreak();
		}
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}