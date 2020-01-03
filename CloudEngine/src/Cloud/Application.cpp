#include "cldpch.h"
#include "Application.h"

#include "Cloud/Input.h"
#include "GLFW/glfw3.h"

namespace Cloud {
	Application* Application::instance = nullptr;

	Application::Application() {
		instance = this;
		WindowProps props;
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));
		window->setVSync(false);

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);
	}

	void Application::run() {
		double lastTime = 0.0;
		
		while (running) {
			//frame rate calculation
			const double time = glfwGetTime();
			const double deltaTime = time - lastTime;
			lastTime = time;
			
			for (Layer* layer : layerStack) {
				layer->onUpdate(deltaTime, time);
			}
			imGuiLayer->begin();
			for (Layer* layer : layerStack) {
				layer->onImGuiRender();
			}
			imGuiLayer->end();
			window->update();
			
			CLD_CORE_TRACE("Framerate: {0}", 1 / (deltaTime == 0 ? 0.0001 : deltaTime));
		}
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

		for (LayerIterator iterator = layerStack.end(); iterator != layerStack.begin();) {
			(*--iterator)->onEvent(event);
			if (event.handled) break;
		}
	}

	void Application::pushLayer(Layer *layer) {
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer *overlay) {
		layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}
		
	bool Application::onWindowClose(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	Application::~Application() = default;
}
