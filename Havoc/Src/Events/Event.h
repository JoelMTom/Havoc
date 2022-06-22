#pragma once

#define BIT(x) 1 << x

namespace Havoc
{
	enum class EventType
	{
		None = 0,
		KeyPressed, KeyReleased,
		MouseButtonPressed, NouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class Event
	{
	public:

		bool m_handled = false;

		virtual ~Event() = default;

		virtual EventType GetEventType() = 0;
		virtual const char* GetName() = 0;
		virtual int GetEventCategoryFlags() = 0;


		inline bool IsInCategory(EventCategory category)
		{
			return GetEventCategoryFlags() & category;

		}
	};
}