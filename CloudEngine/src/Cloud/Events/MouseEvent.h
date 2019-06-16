#pragma once

#include "Event.h"

namespace Cloud {

	class CLOUD_API MousePositionChangedEvent : public Event {
	public:
		MousePositionChangedEvent(float x, float y) : mouseX(x), mouseY(y) {}

		inline float getX() const { return mouseX; }
		inline float getY() const { return mouseY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_POSITION_CHANGED)
		EVENT_SET_CATEGORY(MOUSE | INPUT)
	private:
		float mouseX;
		float mouseY;
	};

	class CLOUD_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x, float y) : offsetX(x), offsetY(y) {}

		inline float getXOffset() const { return offsetX; }
		inline float getYOffset() const { return offsetY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << offsetX << ", " << offsetY;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_SCROLLED)
		EVENT_SET_CATEGORY(MOUSE | INPUT)
	private:
		//some mice have horizontal scrolling
		float offsetX;
		float offsetY;
	};

	class CLOUD_API MouseButtonEvent : public Event {
	public:
		inline int getMouseButton() const { return mouseButton; }
		EVENT_SET_CATEGORY(MOUSE | INPUT)
	protected:
		MouseButtonEvent(int mouseButton) : mouseButton(mouseButton) {}
		int mouseButton;
	};

	class CLOUD_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int mouseButton) : MouseButtonEvent(mouseButton) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mouseButton;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_BUTTON_PRESSED)
	};

	class CLOUD_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int mouseButton) : MouseButtonEvent(mouseButton) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mouseButton;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_BUTTON_RELEASED)
	};
}