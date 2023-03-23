#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "Havoc/Core/Log.h"

namespace Havoc
{
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Havoc::ShaderDataType::Float:    return GL_FLOAT;
		case Havoc::ShaderDataType::Float2:   return GL_FLOAT;
		case Havoc::ShaderDataType::Float3:   return GL_FLOAT;
		case Havoc::ShaderDataType::Float4:   return GL_FLOAT;
		case Havoc::ShaderDataType::Mat3:     return GL_FLOAT;
		case Havoc::ShaderDataType::Mat4:     return GL_FLOAT;
		case Havoc::ShaderDataType::Int:      return GL_INT;
		case Havoc::ShaderDataType::Int2:     return GL_INT;
		case Havoc::ShaderDataType::Int3:     return GL_INT;
		case Havoc::ShaderDataType::Int4:     return GL_INT;
		case Havoc::ShaderDataType::Bool:     return GL_BOOL;
		}

		H_CORE_ERROR("Unknown ShaderDataType!");
		__debugbreak();
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		if (!vertexbuffer->GetLayout().GetElements().size())
		{
			H_CORE_ERROR("Vertex buffer has not layout");
			__debugbreak();
		}

		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexbuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer)
	{
		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}
}