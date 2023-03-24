#pragma once

#include "RendererAPI.h"

namespace Havoc
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void ClearColor()
		{
			s_RendererAPI->ClearColor();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexbuffer)
		{
			s_RendererAPI->DrawIndexed(vertexbuffer);
		}

	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};
}
