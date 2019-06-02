#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h" 
#include "Cloud/Events/ApplicationEvent.h"

namespace Cloud {
	class CLOUD_API Application {
	public:
		Application();
		
		void run();
		void onEvent(Event& e);

		virtual ~Application();
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	Application* createApplication();
}