#pragma once

#include "Cloud/Rendering/Context.h"

struct GLFWwindow;

namespace Cloud {
	class OpenGLContext : public Context {
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* window;
	};
}