#include <CloudEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public Cloud::Layer {
public:
	ExampleLayer(const std::string& name = "Example") : Layer(name), name(name) {}
	
	virtual void onUpdate() override {
		CLD_INFO("Updating layer {0}", name);
	}

	virtual void onImGuiRender() override {
		ImGui::Begin("User window");
		ImGui::Text("Hello World!");		
		ImGui::NewLine();
		ImGui::Text("This line was written by the user!\nHmm this UI could be cooler! >:D");
		ImGui::End();

		ImGui::Begin("PRESS TAB");
		ImGui::Text((const char*)thingy.c_str());
		ImGui::End();
	}

	virtual void onEvent(Cloud::Event& event) override {
		if (event.getEventType() == Cloud::EventType::KEY_PRESSED) {
			Cloud::KeyPressedEvent& e = (Cloud::KeyPressedEvent&)event;
			if (e.getKeyCode() == KEY_TAB) {
				thingy = "Hey! You pressed TAB";
			}
			else {
				thingy = "You did not press TAB... you pressed: " + std::to_string(e.getKeyCode());
			}
		}
	}
private:
	std::string thingy = "nothing pressed yet..";
	std::string name;
};


class App : public Cloud::Application {
public:
	App() {
		pushLayer(new ExampleLayer("Application"));
	}
	~App() {
		
	}
};

Cloud::Application* Cloud::createApplication() {
	return new App();
}