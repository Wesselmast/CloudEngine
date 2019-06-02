#pragma once

#include "Cloud/Window.h"
#include <glfw/glfw3.h>

namespace Cloud {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& windowProps);

		inline unsigned int getWidth() const override { return data.width; }
		inline unsigned int getHeight() const override { return data.height; }
		inline bool isVSync() const override { return data.vSync; }

		inline void setEventCallback(const EventCallbackFunc& callback) override { 
			data.eventCallback = callback; 
		}

		void update() override;
		void setVSync(bool enabled) override;

		virtual ~WindowsWindow();
	private:
		virtual void init(const WindowProps& windowProps);
		virtual void shutdown();
	private:
		GLFWwindow* window;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;

			EventCallbackFunc eventCallback;
		} data;
	};
}