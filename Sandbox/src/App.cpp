#include <iostream>
#include <CloudEngine.h>

class App : public Cloud::Application {
public:
	App() {}




	~App() {}
};

Cloud::Application* Cloud::createApplication() {
	return new App();
}