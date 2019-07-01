#include <iostream>
#include <CloudEngine.h>

class ExampleLayer : public Cloud::Layer {
public:
	ExampleLayer(const std::string& name = "Example") : Layer(name), name(name) {}
	
	virtual void onUpdate() override {
		CLD_INFO("Updating layer {0}", name);
	}

	virtual void onEvent(Cloud::Event& event) override {
		CLD_TRACE("{0}", event);
	}
private:
	std::string name;
};


class App : public Cloud::Application {
public:
	virtual void begin() override {
		pushLayer(new ExampleLayer("Application"));
		pushOverlay(new Cloud::ImGuiLayer());
		
		CLD_WARN("Starting up the application");
	} 

	virtual void update() override {
		CLD_ERROR(Cloud::Input::mousePressed(MOUSE_BTN_1));
	} 
};

Cloud::Application* Cloud::createApplication() {
	return new App();
}