#pragma once

#include <memory>
#include <functional>

#include "Havoc/Events/Event.h"

namespace Havoc
{
	struct WindowProperties
	{
		const char* Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const char* title, uint32_t width, uint32_t height)
			: Title(title), Width(width), Height(height)
		{

		}

	};

	class Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static std::unique_ptr<Window> Create(const WindowProperties& props = WindowProperties("Havoc Engine", 1280, 720));
	};
}	