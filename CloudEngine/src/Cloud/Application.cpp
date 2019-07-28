#include "cldpch.h"
#include "Application.h"

#include "Cloud/Input.h"
#include <glad/glad.h>

namespace Cloud {
	Application* Application::instance = nullptr;

	Application::Application() {
		instance = this;
		WindowProps props("CloudEngine v0.0  | FPS: " + std::to_string(frameRate));
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertexPostitions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPostitions), vertexPostitions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		const char* vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec2 aPosition;

			out vec2 vPosition;

			void main()  {
				vPosition = aPosition;
				gl_Position = vec4(aPosition, 0.0, 1.0);
			}
		)";

		const char* pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			in vec2 vPosition;

			void main()  {
				oColor = vec4(vPosition * -0.5 + 0.5, 0.5, 1.0);
			}
		)";
		
		shader.reset(new Shader(vertexSrc, pixelSrc));
	}

	void Application::run() {
		begin();

		while (running) {
			glClear(GL_COLOR_BUFFER_BIT);

			shader->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack) {
				layer->onUpdate();
			}

			imGuiLayer->begin();
			for (Layer* layer : layerStack) {
				layer->onImGuiRender();
			}
			imGuiLayer->end();

			update();
			window->update();
		}
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

		for (LayerIterator iterator = layerStack.end(); iterator != layerStack.begin();) {
			(*--iterator)->onEvent(event);
			if (event.Handled) break;
		}
	}

	void Application::pushLayer(Layer *layer) {
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer *overlay) {
		layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}
		
	bool Application::onWindowClose(WindowCloseEvent& e) {
		running = false;
		return true;
	}

	Application::~Application() {
	}
}