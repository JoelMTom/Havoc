#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Havoc/Renderer/Renderer.h"
#include "Havoc/Core/Log.h"

namespace Havoc
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("RendererAPI::None not supported!"); __debugbreak(); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		H_CORE_ERROR("Unknown Renderer!");
		__debugbreak();
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			H_CORE_ERROR("RendererAPI::None not supported!"); __debugbreak(); return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		H_CORE_ERROR("Unknown Renderer!");
		__debugbreak();
		return nullptr;
		
	}
}	