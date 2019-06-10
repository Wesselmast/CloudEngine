#include <iostream>
#include <CloudEngine.h>

class ExampleLayer : public Cloud::Layer {
public:
	ExampleLayer(const std::string& name = "Example") : Layer(name), name(name) {}
	
	void onUpdate() override { 
		CLD_INFO("Updating layer {0}", name);
	}

	void onEvent(Cloud::Event& event) override {
		CLD_TRACE("{0}", event);
	}
private:
	std::string name;
};


class App : public Cloud::Application {
public:
	App() {
		pushLayer(new ExampleLayer("AppLayer"));
	}
	~App() {}
};

Cloud::Application* Cloud::createApplication() {
	return new App();
}