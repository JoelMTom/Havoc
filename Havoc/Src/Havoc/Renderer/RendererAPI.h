#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Havoc
{
	class RendererAPI
	{
 	public:

		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void ClearColor() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexarray) = 0;

		inline static API GetAPI() { return s_API; }

		static std::unique_ptr<RendererAPI> Create();

	private:
		static API s_API;
	};
}