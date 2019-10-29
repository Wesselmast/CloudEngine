#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h" 
#include "Cloud/Events/ApplicationEvent.h"

#include "Cloud/ImGui/ImGuiLayer.h"
#include "Cloud/Rendering/Shader.h"
#include "Cloud/Rendering/Buffers/VertexBuffer.h"
#include "Cloud/Rendering/Buffers/IndexBuffer.h"
#include "Cloud/Rendering/VertexArray.h"

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

		std::shared_ptr<Shader> shader;
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};

	Application* createApplication();
}