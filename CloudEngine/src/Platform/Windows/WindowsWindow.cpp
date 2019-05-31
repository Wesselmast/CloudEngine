#include "cldpch.h"
#include "WindowsWindow.h"

namespace Cloud {
	static bool firstTime = true;

	Window* Window::create(const WindowProps& windowProps) {
		return new WindowsWindow(windowProps);
	}

	WindowsWindow::WindowsWindow(const WindowProps& windowProps) {
		init(windowProps);
	}

	void WindowsWindow::init(const WindowProps& windowProps) {
		data.title = windowProps.title;
		data.width = windowProps.width;
		data.height = windowProps.height;

		CLD_CORE_INFO("Creating window...");

		if (firstTime) {
			auto success = glfwInit();
			//if no success, break here and log this message
			CLD_CORE_ASSERT(success, "Could not initialize glfw!");
			firstTime = false;
		}

		window = glfwCreateWindow((int)windowProps.width,
								  (int)windowProps.height,
								  data.title.c_str(),
								  nullptr, nullptr);
		//make context current on main thread to avoid pipeline flush
		glfwMakeContextCurrent(window);
		//make it so I can use the data struct when creating a callback to an event
		//example: I want the width/height/callback when resizing the window
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);
	}

	void WindowsWindow::update() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::setVSync(bool enabled) {
		data.vSync = enabled;
		if (enabled) {
			glfwSwapInterval(1);
			return;
		}
		glfwSwapInterval(0);
	}

	void WindowsWindow::shutdown() {
		glfwDestroyWindow(window);
	}

	WindowsWindow::~WindowsWindow() {
		shutdown();
	}
}