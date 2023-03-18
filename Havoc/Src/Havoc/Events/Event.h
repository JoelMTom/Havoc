#pragma once
#include <string>

#define BIT(x) 1 << x

namespace Havoc
{
	enum class EventType
	{
		None = 0,
		KeyPressed, KeyReleased, KeyTyped,
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

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

	class Event
	{
	public:

		bool m_handled = false;

		virtual ~Event() = default;

		virtual EventType GetEventType() const  = 0;
		virtual const char* GetName() const  = 0;
		virtual int GetEventCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }


		inline bool IsInCategory(EventCategory category)
		{
			return GetEventCategoryFlags() & category;

		}
	};
}