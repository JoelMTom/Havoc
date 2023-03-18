#pragma once

#include <memory>

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
		
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		static std::unique_ptr<Window> Create(const WindowProperties& props = WindowProperties("Havoc Engine", 720, 600));
	};
}	