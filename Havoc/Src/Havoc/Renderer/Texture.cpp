#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "Renderer.h"
#include "Havoc/Core/Log.h"

namespace Havoc
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("Shader for RendererAPI::None is not supported"); __debugbreak();
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		H_CORE_ERROR("Could initialize shader!");
		__debugbreak();
		return nullptr;
	}
}