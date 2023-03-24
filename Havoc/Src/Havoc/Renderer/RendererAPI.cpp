#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Havoc
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("RendererAPI::None is not currently supported!"); __debugbreak(); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLRendererAPI>();
		}

		H_CORE_ERROR("Unknown RendererAPI!"); 
		__debugbreak(); 
		return nullptr;
	}
}