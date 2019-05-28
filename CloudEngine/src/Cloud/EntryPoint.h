#pragma once

#ifdef CLD_PLATFORM_WINDOWS

extern Cloud::Application* Cloud::createApplication();

int main(int argc, char** argv) {
	auto app = Cloud::createApplication();
	app->run();
	delete app;
	return 0;
}

#else
	#error CloudEngine only supports windows!
#endif