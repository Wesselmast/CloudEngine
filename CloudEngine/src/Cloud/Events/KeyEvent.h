#pragma once

#include "Event.h"

namespace Cloud {

	class CLOUD_API KeyEvent : public Event {
	public:
		inline int getKeyCode() const { return keyCode; }
		EVENT_SET_CATEGORY(KEYBOARD | INPUT)
	protected:
		KeyEvent(int keyCode) : keyCode(keyCode) {}
		int keyCode;
	};

	class CLOUD_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}
		inline int getRepeatCount() const { return repeatCount; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_SET_TYPE(KEY_PRESSED)
	private:
		int repeatCount;
	};

	class CLOUD_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_SET_TYPE(KEY_RELEASED)
	};

	class CLOUD_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keyCode;
			return ss.str();
		} 

		EVENT_SET_TYPE(KEY_TYPED)
	};
}
