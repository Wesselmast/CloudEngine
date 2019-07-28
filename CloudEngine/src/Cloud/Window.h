#pragma once

#include "cldpch.h"

#include "Cloud/Core.h"
#include "Cloud/Events/Event.h"

namespace Cloud {
	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "CloudEngine v0.0", 
					unsigned int width = 1280, 
					unsigned int height = 720) 
			: title(title), width(width), height(height)  {
		}
	};

	class  Window {
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual void update() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		//platform-agnostic function to create a window, static because there can only be one
		static Window* create(const WindowProps& windowProps = WindowProps());

		virtual ~Window() {}
	};
}