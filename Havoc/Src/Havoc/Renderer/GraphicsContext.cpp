#include "GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Renderer.h"
#include "Havoc/Core/Log.h"

namespace Havoc
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			H_CORE_ERROR("RendererAPI::None not supported!"); __debugbreak(); return nullptr;
		case RendererAPI::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		H_CORE_ERROR("Unknown RendererAPI");
		__debugbreak();
		return nullptr;
	}
}