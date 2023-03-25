#pragma once

#include "Havoc/Renderer/Shader.h"

namespace Havoc
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexsrc, const std::string& fragmentsrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID;
	};
}