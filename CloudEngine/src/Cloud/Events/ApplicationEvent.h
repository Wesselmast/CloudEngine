#pragma once

#include "Event.h"

namespace Cloud {
	class  WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

		inline unsigned int getWidth() { return width; }
		inline unsigned int getHeight() { return height; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str();
		}

		EVENT_SET_CATEGORY(APPLICATION)
		EVENT_SET_TYPE(WINDOW_RESIZE)
	private:
		unsigned int width;
		unsigned int height;
	};

	class  WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_SET_CATEGORY(APPLICATION)
		EVENT_SET_TYPE(WINDOW_CLOSE)
	};

	class  AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		EVENT_SET_CATEGORY(APPLICATION)
		EVENT_SET_TYPE(APP_TICK)
	};

	class  AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_SET_CATEGORY(APPLICATION)	
		EVENT_SET_TYPE(APP_UPDATE)
	};

	class  AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}

		EVENT_SET_CATEGORY(APPLICATION)
		EVENT_SET_TYPE(APP_RENDER)
	};

}