#pragma once

#include "Havoc/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Havoc
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexsrc, const std::string& fragmentsrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformInt(const std::string& name, int value) override;

		virtual void UploadUniformFloat$(const std::string& name, const glm::vec4& values) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual const std::string& GetName() const override { return m_Name; }

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}