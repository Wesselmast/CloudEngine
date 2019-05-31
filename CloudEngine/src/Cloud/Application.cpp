#include "cldpch.h"
#include "Application.h"

#include "Cloud/Events/ApplicationEvent.h"
#include <glfw/glfw3.h>

namespace Cloud {
	Application::Application() {
		window = std::unique_ptr<Window>(Window::create());
	}

	void Application::run() {
		while (running) {
			glClearColor(.85, .5, .1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->update();
		}
	}

	Application::~Application() {
	}
}