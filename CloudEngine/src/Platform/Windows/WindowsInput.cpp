#include "cldpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include <Cloud/Application.h>

namespace Cloud {
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::isKeyPressed(int keycode) {
		int state = glfwGetKey(static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow()), keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMousePressed(int button) {
		bool state = glfwGetMouseButton(static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow()), button);
		return state == GLFW_PRESS;
	}

	glm::vec2 WindowsInput::getMousePos() {
		double x, y;
		glfwGetCursorPos(static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow()), &x, &y);
		return glm::vec2(x, y);
	}
	 
	float WindowsInput::getMouseX() {
		return getMousePos().x;
	}

	float WindowsInput::getMouseY() {
		return getMousePos().y;
	}
}