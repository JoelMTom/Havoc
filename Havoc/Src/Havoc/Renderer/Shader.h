#pragma once

#include <string>
#include <memory>


namespace Havoc
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& vertexsrc, const std::string& fragmentsrc);
	};
}