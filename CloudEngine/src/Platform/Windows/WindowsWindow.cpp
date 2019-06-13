#include "cldpch.h"
#include "WindowsWindow.h"

#include "Cloud/Events/ApplicationEvent.h"
#include "Cloud/Events/KeyEvent.h"
#include "Cloud/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Cloud {
	static bool firstTime = true;

	static void glfwErrorCallback(int error, const char* description) {
		CLD_CORE_ERROR("glfw error ({0}): {1}", error, description);
	}

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
			glfwSetErrorCallback(glfwErrorCallback);
			firstTime = false;
		}

		window = glfwCreateWindow((int)windowProps.width,
								 (int)windowProps.height,
								 data.title.c_str(),
								 nullptr, nullptr);
		//make context current on main thread to avoid pipeline flush
		glfwMakeContextCurrent(window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CLD_CORE_ASSERT(status, "Could not initialize Glad!");
		//make it so I can use the data struct when creating a callback to an event
		//example: I want the width/height/callback when resizing the window
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent resizeEvent(width, height);
			data.eventCallback(resizeEvent);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent closeEvent;
			data.eventCallback(closeEvent);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent keyEvent(key, 0);
					data.eventCallback(keyEvent);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent keyEvent(key);
					data.eventCallback(keyEvent);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent keyEvent(key, 1);
					data.eventCallback(keyEvent);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent mouseEvent(button);
					data.eventCallback(mouseEvent);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent mouseEvent(button);
					data.eventCallback(mouseEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent mouseScrollEvent(xOffset, yOffset);
			data.eventCallback(mouseScrollEvent);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MousePositionChanged mousePositionEvent(xPos, yPos);
			data.eventCallback(mousePositionEvent);
		});
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