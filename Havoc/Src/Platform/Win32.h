#pragma once

#include "Core/Window.h"
#include "Core/Log.h"

namespace Havoc
{
	class Win32 : public Window
	{
	public:

		Win32(const WindowProperties& props);
		virtual ~Win32();

		void OnUpdate() override;

		void Init(const WindowProperties& props);
		void shutdown();

	private:

		struct WinData
		{
			const char* title;
			unsigned int width;
			unsigned int height;
		};

		WinData m_data;
	};
}