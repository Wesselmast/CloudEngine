#pragma once

#include "Event.h"

namespace Cloud {

	class  MousePositionChangedEvent : public Event {
	public:
		MousePositionChangedEvent(double x, double y) : mouseX(x), mouseY(y) {}

		inline double getX() const { return mouseX; }
		inline double getY() const { return mouseY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_POSITION_CHANGED)
		EVENT_SET_CATEGORY(MOUSE | INPUT)
	private:
		double mouseX;
		double mouseY;
	};

	class  MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(double x, double y) : offsetX(x), offsetY(y) {}

		inline double getXOffset() const { return offsetX; }
		inline double getYOffset() const { return offsetY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << offsetX << ", " << offsetY;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_SCROLLED)
		EVENT_SET_CATEGORY(MOUSE | INPUT)
	private:
		//some mice have horizontal scrolling
		double offsetX;
		double offsetY;
	};

	class  MouseButtonEvent : public Event {
	public:
		inline int getMouseButton() const { return mouseButton; }
		EVENT_SET_CATEGORY(MOUSE | INPUT)
	protected:
		MouseButtonEvent(int mouseButton) : mouseButton(mouseButton) {}
		int mouseButton;
	};

	class  MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int mouseButton) : MouseButtonEvent(mouseButton) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mouseButton;
			return ss.str();
		}

		EVENT_SET_TYPE(MOUSE_BUTTON_PRESSED)
	};

	class  MouseButtonReleasedEvent : public MouseButtonEvent {
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