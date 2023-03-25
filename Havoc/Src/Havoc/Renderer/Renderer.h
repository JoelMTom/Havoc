#pragma once

#include "RendererAPI.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Havoc
{

	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader , const std::shared_ptr<VertexArray>& vertexarray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}