#include "VertexArray.h"

#include "Havoc/Core/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Havoc
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			H_CORE_ERROR("RendererAPI::None not supported!"); __debugbreak(); return nullptr;
		case RendererAPI::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		H_CORE_ERROR("Unknown Renderer::API");
		__debugbreak();
		return nullptr;
	}
}