#include "Renderer.h"

#include "RenderCommand.h"

namespace Havoc
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}


	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexarray)
	{
		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);
	}
}