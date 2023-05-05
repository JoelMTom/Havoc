#pragma once

#include "Havoc/Renderer/RendererAPI.h"

namespace Havoc
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void ClearColor() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexarray) override;
	};
}