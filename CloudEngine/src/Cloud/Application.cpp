#include "cldpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Cloud {
	Application* Application::instance = nullptr;

	Application::Application() {
		instance = this;
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));
	}

	void Application::run() {
		while (running) {
			glClearColor(.85, .5, .1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack) {
				layer->onUpdate();
			}

			window->update();
		}
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

		for (LayerIterator iterator = layerStack.end(); iterator != layerStack.begin();) {
			(*--iterator)->onEvent(event);
			if (event.Handled) break;
		}
	}

	void Application::pushLayer(Layer * layer) {
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer * overlay) {
		layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}
		
	bool Application::onWindowClose(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	Application::~Application() {
	}
}