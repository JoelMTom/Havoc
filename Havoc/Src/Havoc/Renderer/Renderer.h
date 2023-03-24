#pragma once

#include "RendererAPI.h"

namespace Havoc
{

	class Renderer
	{
	public:

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexarray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}