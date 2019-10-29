#include "cldpch.h"
#include "Application.h"

#include "Cloud/Input.h"
#include <glad/glad.h>

namespace Cloud {
	Application* Application::instance = nullptr;

	Application::Application() {
		instance = this;
		WindowProps props;
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FUNC(Application::onEvent));

		imGuiLayer = new ImGuiLayer();
		pushOverlay(imGuiLayer);

		float vertices[] = {
			 0.0f,   0.75f, 1.0f, 0.0f, 0.5f, 0.0f,
			 0.5f,   0.0f,	1.0f, 1.0f, 1.0f, 0.0f,
			 0.25f, -0.75f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.75f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,   0.0f,	1.0f, 1.0f, 1.0f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4
		};

		vertexArray.reset(VertexArray::create());
		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::FLOAT2, "aPosition" },
			{ ShaderDataType::FLOAT4, "aColor" }
		};

		vertexBuffer->setLayout(layout);
		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));

		vertexArray->addVertexBuffer(vertexBuffer);
		vertexArray->setIndexBuffer(indexBuffer);
		
		const char* vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec2 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec2 vPosition;
			out vec4 vColor;

			void main()  {
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = vec4(aPosition, 0.0, 1.0);
			}
		)";

		const char* pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			in vec2 vPosition;
			in vec4 vColor;
			uniform float uRed;

			void main()  {
				oColor = vColor * (uRed + 0.5); //vec4(vPosition * -0.5 + uRed, 0.5, 1.0);
			}
		)";
		
		shader.reset(Shader::create(vertexSrc, pixelSrc));
	}

	void Application::run() {
		begin();

		double deltaTime = 0.0f;
		double time = 0.0f;

		while (running) {
			clock_t beginFrame = clock();

			glClear(GL_COLOR_BUFFER_BIT);

			shader->bind();
			vertexArray->bind();

			int uRed = shader->getUniformLocation("uRed");
			glUniform1f(uRed, sin(time) * 0.5 + 0.5);
			glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
			

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

			//frame rate calculation
			deltaTime = (clock() - beginFrame) / (double)CLOCKS_PER_SEC;
			time += deltaTime;
			
			if (deltaTime > 0.0) {
				CLD_CORE_TRACE("Framerate: {0}", 1 / deltaTime);
			}
		}
	}

	void Application::onEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::onWindowClose));

		for (LayerIterator iterator = layerStack.end(); iterator != layerStack.begin();) {
			(*--iterator)->onEvent(event);
			if (event.handled) break;
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

	Application::~Application() = default;
}
