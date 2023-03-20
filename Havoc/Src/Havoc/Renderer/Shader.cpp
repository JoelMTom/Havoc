#include "Shader.h"
#include "Renderer.h"

#include "Havoc/Core/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Havoc
{
	Shader* Shader::Create(const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			H_CORE_ERROR("Shader for RendererAPI::None is not supported"); __debugbreak();
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexsrc, fragmentsrc);
		}

		H_CORE_ERROR("Could initialize shader!");
		__debugbreak();
		return nullptr;
	}
}