#pragma once

#include <string>
#include <memory>

#include <glm/glm.hpp>

namespace Havoc
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		static std::shared_ptr<Shader> Create(const std::string& vertexsrc, const std::string& fragmentsrc);
	};
}