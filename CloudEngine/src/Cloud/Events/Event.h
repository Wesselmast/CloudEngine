#pragma once

#include "cldpch.h"
#include "Cloud/Core.h"

namespace Cloud {

	enum class EventType {
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_POSITION_CHANGED, MOUSE_SCROLLED
	};

	//filter for sorting events, bitfield because you might want multiple categories for one event
	//not enum class because we want those bitwise operations
	enum EventCategory {
		NONE			= 0,
		APPLICATION		= 1 << 0,
		INPUT			= 1 << 1,
		KEYBOARD		= 2 << 1,
		MOUSE			= 3 << 1,
		MOUSE_BUTTON	= 4 << 1
	};

	//these macros are here to avoid repeating these lines of code and clogging up the codebase
	//I use a static function getType() so that you can get the EventType statically instead of needing an instance
#define EVENT_SET_TYPE(type) static EventType getType() { return EventType::##type; }\
							 virtual EventType getEventType() const override { return getType(); }\
							 virtual const char* getName() const override { return #type; }
	
#define EVENT_SET_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class Event {
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }
		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}
	public:
		bool handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : event(event) { }

		template<typename T>
		bool dispatch(EventFunc<T> func) {
			if (event.getEventType() != T::getType()) {
				return false;
			}
			event.handled = func(*(T*)&event);
			return true;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.toString();
	}
}