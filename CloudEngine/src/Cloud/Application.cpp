#include "cldpch.h"
#include "Application.h"

#include "Cloud/Events/ApplicationEvent.h"
#include "Cloud/Log.h"

namespace Cloud {
	Application::Application() {
	}

	void Application::run() {
		WindowResizeEvent e(1920, 1080);
		CLD_INFO(e);

		while (true);
	}

	Application::~Application() {
	}
}