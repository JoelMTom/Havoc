#pragma once

#include <stdint.h>
#include <memory>

namespace Havoc
{
	struct WindowProperties
	{
		const char* m_title;
		uint32_t m_width;
		uint32_t m_height;

		WindowProperties(const char* title, uint32_t width, uint32_t height)
			: m_title(title), m_width(width), m_height(height)
		{

		}

	};

	class Window
	{
	public:
		
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		static std::unique_ptr<Window> Create(const WindowProperties& props = WindowProperties("Havoc Engine", 720, 600));

	private:
		const char* m_windowName;
		int m_width = 720;
		int m_height = 600;
	};
}