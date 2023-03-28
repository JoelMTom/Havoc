#pragma once

#include <string>

#include "Havoc/Events/Event.h"
#include "Havoc/Core/TimeStep.h"

namespace Havoc
{
	class Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnEvent(Event& event) {};

		const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}