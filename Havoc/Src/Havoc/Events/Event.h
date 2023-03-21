#pragma once
#include <string>

#define BIT(x) 1 << x

namespace Havoc
{
	enum class EventType
	{
		None = 0,
		WindowResize, WindowClose,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, NouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
		EventCategoryApplication	= BIT(5)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

	class Event
	{
	public:

		bool Handled = false;

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

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			:m_Event(event) {}

		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};
}