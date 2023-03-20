#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Havoc/Renderer/Renderer.h"
#include "Havoc/Core/Log.h"

namespace Havoc
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			H_CORE_ERROR("RendererAPI::None not supported!"); __debugbreak(); return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		H_CORE_ERROR("Unknown Renderer!");
		__debugbreak();
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		return new OpenGLIndexBuffer(indices, count);
	}
}	