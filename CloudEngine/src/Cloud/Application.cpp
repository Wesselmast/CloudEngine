#include "cldpch.h"
#include "Application.h"

#include <glfw/glfw3.h>

namespace Cloud {
#define BIND_EVENT_FUNC(func)std::bind(&func, this, std::placeholders::_1)

	Application::Application() {
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));
	}

	void Application::run() {
		while (running) {
			glClearColor(.85, .5, .1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->update();
		}
	}

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

		CLD_CORE_TRACE("{0}", e);
	}
		
	bool Application::onWindowClose(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	Application::~Application() {
	}
}