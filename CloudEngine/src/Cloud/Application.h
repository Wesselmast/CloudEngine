#pragma once

#include "Core.h"
#include "Events/Event.h" 

namespace Cloud {
	class CLOUD_API Application {
	public:
		Application();

		void run();

		virtual ~Application();
	};

	Application* createApplication();
}