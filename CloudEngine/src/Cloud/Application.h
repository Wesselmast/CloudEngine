#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h" 
#include "Cloud/Events/ApplicationEvent.h"
#include "Cloud/ImGui/ImGuiLayer.h"


namespace Cloud {
	class Application {
	public:
		Application();
		
		void run();
		void onEvent(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static Application& get() { return *instance; }
		inline Window& getWindow() { return *window; }

		virtual ~Application();
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		static Application* instance;
		LayerStack layerStack;
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
	};

	Application* createApplication();
}