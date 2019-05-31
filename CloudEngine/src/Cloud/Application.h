#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h" 

namespace Cloud {
	class CLOUD_API Application {
	public:
		Application();
		void run();
		virtual ~Application();
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	Application* createApplication();
}