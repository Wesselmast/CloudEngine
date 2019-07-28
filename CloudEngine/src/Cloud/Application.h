#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h" 
#include "Cloud/Events/ApplicationEvent.h"

#include "Cloud/ImGui/ImGuiLayer.h"
#include "Cloud/Rendering/Shader.h"

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

		virtual void begin() {}
		virtual void update() {}

		virtual ~Application();
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		static Application* instance;
		LayerStack layerStack;
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
		float frameRate = 0;

		unsigned int vertexArray;
		unsigned int vertexBuffer;
		unsigned int indexBuffer;

		std::unique_ptr<Shader> shader;
	};

	Application* createApplication();
}