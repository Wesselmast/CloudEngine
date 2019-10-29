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
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(window);
	}
}