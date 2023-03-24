#include "Shader.h"
#include "Renderer.h"

#include "Havoc/Core/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Havoc
{
	std::shared_ptr<Shader> Shader::Create(const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("Shader for RendererAPI::None is not supported"); __debugbreak();
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexsrc, fragmentsrc);
		}

		H_CORE_ERROR("Could initialize shader!");
		__debugbreak();
		return nullptr;
	}
}