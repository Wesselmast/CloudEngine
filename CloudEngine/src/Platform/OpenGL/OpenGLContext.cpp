#include "cldpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cloud {
	OpenGLContext::OpenGLContext(GLFWwindow *window) : window(window) {
	}

	void OpenGLContext::init() {
		//make context current on main thread to avoid pipeline flush
		glfwMakeContextCurrent(window);
		//glfwSwapInterval(1);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CLD_CORE_ASSERT(status, "Could not initialize Glad!");

		glEnable(GL_DEPTH_TEST);

		if (FULLSCREEN) {
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(window);
	}
}