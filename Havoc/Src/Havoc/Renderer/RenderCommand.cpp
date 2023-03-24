#include "RenderCommand.h"

namespace Havoc
{
	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}