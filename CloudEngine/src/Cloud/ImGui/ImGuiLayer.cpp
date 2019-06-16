#include "cldpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Cloud/Application.h"

//TEMP
#include <glad/glad.h>
#include <GLFW/glfw3.h>	

namespace Cloud {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	}

	void ImGuiLayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors | 
						   ImGuiBackendFlags_HasSetMousePos;


		//TEMPORARY
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach() {
	}

	void ImGuiLayer::onUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		float currentTime = (float)glfwGetTime();
		io.DeltaTime = time > 0.0f ? (currentTime - time) : (1.0f / 60.0f);
		time = currentTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event & event) {
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.MouseDown[event.getMouseButton()] = true;

			return false;
		});

		dispatcher.dispatch<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.MouseDown[event.getMouseButton()] = false;

			return false;
		});

		dispatcher.dispatch<MousePositionChangedEvent>([](MousePositionChangedEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.MousePos = ImVec2(event.getX(), event.getY());

			return false;
		});

		dispatcher.dispatch<MouseScrolledEvent>([](MouseScrolledEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.MouseWheel += event.getXOffset();
			io.MouseWheelH += event.getYOffset();

			return false;
		});

		dispatcher.dispatch<KeyTypedEvent>([](KeyTypedEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			int keyCode = event.getKeyCode();

			if (keyCode > 0 && keyCode < 0x10000) {
				io.AddInputCharacter((unsigned short)keyCode);
			}
			return false;
		});

		dispatcher.dispatch<KeyPressedEvent>([](KeyPressedEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.KeysDown[event.getKeyCode()] = true;

			io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] | io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] | io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] | io.KeysDown[GLFW_KEY_RIGHT_ALT];
			io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] | io.KeysDown[GLFW_KEY_RIGHT_SUPER];

			return false;
		});

		dispatcher.dispatch<KeyReleasedEvent>([](KeyReleasedEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.KeysDown[event.getKeyCode()] = false;

			io.KeyCtrl = false;
			io.KeyShift = false;
			io.KeyAlt = false;
			io.KeySuper = false;

			return false;
		});

		dispatcher.dispatch<WindowResizeEvent>([](WindowResizeEvent &event) {
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
			io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
			glViewport(0, 0, event.getWidth(), event.getHeight());

			return false;
		});
	}
	
	ImGuiLayer::~ImGuiLayer() {
	}
}
