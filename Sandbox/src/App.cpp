#include <CloudEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public Cloud::Layer {
public:
	ExampleLayer(const std::string& name = "Example") : Layer(name), name(name), camera(-1.6f, 1.6, -0.9f, 0.9f) {

		float vertices[] = {
			 0.75f,   0.0f,	1.0f, 1.0f, 1.0f, 0.0f,
			 0.33f, -0.75f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.33f, -0.75f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.75f,   0.0f,	1.0f, 1.0f, 1.0f, 0.0f,
			 0.0f,   0.75f, 1.0f, 0.0f, 0.5f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4
		};

		vertexArray.reset(Cloud::VertexArray::create());
		vertexBuffer.reset(Cloud::VertexBuffer::create(vertices, sizeof(vertices)));

		Cloud::BufferLayout layout = {
			{Cloud::ShaderDataType::FLOAT2, "aPosition" },
			{Cloud::ShaderDataType::FLOAT4, "aColor" }
		};

		vertexBuffer->setLayout(layout);
		indexBuffer.reset(Cloud::IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));

		vertexArray->addVertexBuffer(vertexBuffer);
		vertexArray->setIndexBuffer(indexBuffer);

		const char* vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec2 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec2 vPosition;
			out vec4 vColor;
			uniform mat4 uViewProjection;

			void main()  {
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = uViewProjection * vec4(aPosition, 0.0, 1.0);
			}
		)";

		const char* pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 oColor;

			in vec4 vColor;
			uniform float uRed;
			uniform vec4 uColor;

			void main()  {
				oColor = vColor * uColor * (uRed + 0.5);
			}
		)";

		shader.reset(Cloud::Shader::create(vertexSrc, pixelSrc));
	}
	
	void onUpdate() override {
		//clock_t beginFrame = clock();
		
		Cloud::RenderCommand::clear();
		camera.setRotation(camera.getRotation() + input.z * deltaTime * 35);
		camera.setPosition(camera.getPosition() + glm::vec3(input.x, input.y, 0.0f) * (float)deltaTime);

		Cloud::Renderer::beginScene(camera);
		{
			shader->uploadUniformF1("uRed", sin(time * speed) * 0.5 + brightness - 0.5f);
			shader->uploadUniformVec4("uColor", color);
			Cloud::Renderer::submit(vertexArray, shader);
		}
		Cloud::Renderer::endScene();

		//frame rate calculation
		deltaTime = 0.015; //(clock() - beginFrame) / (double)CLOCKS_PER_SEC;
		time += deltaTime;

		if (deltaTime > 0.0) {
			CLD_CORE_TRACE("Framerate: {0}", 1 / deltaTime);
		}

		//CLD_CORE_TRACE("PlayerInput \n  X: {0}\n  Y: {1}\n  R: {2}", playerInput.first, playerInput.second, playerRotation);
	}

	void onImGuiRender() override {
		ImGui::Begin("PRESS TAB");
		ImGui::Text(thingy.c_str());
		ImGui::End();

		ImGui::Begin("Shape Customizer");
		ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);
		ImGui::SliderFloat("Speed", &speed, 0.0f, 15.0f);
		ImGui::ColorPicker4("Color", glm::value_ptr(color));
		ImGui::End();
	}

	void onEvent(Cloud::Event& event) override {
		Cloud::KeyPressedEvent& e = (Cloud::KeyPressedEvent&)event;
		switch(event.getEventType()) {
			case Cloud::EventType::KEY_PRESSED: {
				switch (e.getKeyCode()) {
					case KEY_W: input.y =  1.0f; break;
					case KEY_A: input.x = -1.0f; break;
					case KEY_S: input.y = -1.0f; break;
					case KEY_D: input.x =  1.0f; break;
					case KEY_Q: input.z =  1.0f; break;
					case KEY_E: input.z = -1.0f; break;
				}
				thingy = e.getKeyCode() == KEY_TAB ? "Hey! You pressed TAB" : "You did not press TAB... you pressed: " + std::to_string(e.getKeyCode());
			} break;
			case Cloud::EventType::KEY_RELEASED: {
					switch (e.getKeyCode()) {
						case KEY_W: input.y = 0.0f;
						case KEY_A: input.x = 0.0f;
						case KEY_S: input.y = 0.0f;
						case KEY_D: input.x = 0.0f;
						case KEY_Q: input.z = 0.0f;
						case KEY_E: input.z = 0.0f;
					}
				}
			}
		}
private:
	std::string thingy = "nothing pressed yet..";
	std::string name;

	std::shared_ptr<Cloud::Shader> shader;
	std::shared_ptr<Cloud::VertexBuffer> vertexBuffer;
	std::shared_ptr<Cloud::VertexArray> vertexArray;
	std::shared_ptr<Cloud::IndexBuffer> indexBuffer;

	Cloud::OrthoCamera camera;

	std::pair<float, float> playerInput;
	glm::vec3 input = glm::vec3(0, 0, 0);
	float playerRotation = 0;

	double deltaTime = 0.0f;
	double time = 0.0f;

	float brightness = 1.0f;
	float speed = 1.0;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
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