#include <CloudEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public Cloud::Layer {
public:
	ExampleLayer(const std::string& name = "Example") : Layer(name), name(name), camera(68.0f, 1600.0f/900.0f, 0.01f, 15.0f) {

		/*	HEXAGON 2d
			0.75f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		   0.33f, -0.75f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		  -0.33f, -0.75f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		  -0.75f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		   0.0f,   0.75f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f
		*/
		
		float vertices[] = {

			 1.0f,  -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			 1.0f,  -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f,  -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f,  -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			 1.0f,   1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			 1.0f,   1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f,   1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
			-1.0f,   1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		};

		unsigned int indices[] = {
				0, 1, 3, 3, 1, 2,
				1, 5, 2, 2, 5, 6,
				5, 4, 6, 6, 4, 7,
				4, 0, 7, 7, 0, 3,
				3, 2, 7, 7, 2, 6,
				4, 5, 0, 0, 5, 1
		}; 

		vertexArray.reset(Cloud::VertexArray::create());
		vertexBuffer.reset(Cloud::VertexBuffer::create(vertices, sizeof(vertices)));

		Cloud::BufferLayout layout = {
			{Cloud::ShaderDataType::FLOAT3, "aPosition" },
			{Cloud::ShaderDataType::FLOAT4, "aColor" }
		};

		vertexBuffer->setLayout(layout);
		indexBuffer.reset(Cloud::IndexBuffer::create(indices, sizeof(indices) / sizeof(unsigned int)));

		vertexArray->addVertexBuffer(vertexBuffer);
		vertexArray->setIndexBuffer(indexBuffer);

		const char* vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec3 vPosition;
			out vec4 vColor;
			uniform mat4 uViewProjection;

			void main()  {
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = uViewProjection * vec4(aPosition, 1.0) + vec4(0.0, 0.0, -1.0, 0.0);
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
	
	void onUpdate(const float deltaTime, const float time) override {
		Cloud::RenderCommand::clear();
		camera.setRotation(camera.getRotation() + rotation * (float)deltaTime * 0.15f);
		
		forward = normalize(
			glm::vec3(
				cos(glm::radians(camera.getRotation().x)) * cos(camera.getRotation().y),
				sin(camera.getRotation().y),
				sin(glm::radians(camera.getRotation().x)) * cos(camera.getRotation().y)
			)
		);
		right = normalize(cross(forward, glm::vec3(0, 1, 0)));
		up = normalize(cross(right, forward));
		
		rotation = glm::vec3(0, 0, 0);
		camera.setPosition(camera.getPosition() + input * (float)deltaTime * cameraSpeed);


		Cloud::Renderer::beginScene(camera);
		{
			shader->uploadUniformF1("uRed", sin(time * speed) * 0.5 + brightness - 0.5);
			shader->uploadUniformVec4("uColor", color);
			Cloud::Renderer::submit(vertexArray, shader);
		}
		Cloud::Renderer::endScene();
	}

	void onImGuiRender() override {
		ImGui::Begin("Shape Customizer");
		ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);
		ImGui::SliderFloat("Speed", &speed, 0.0f, 15.0f);
		ImGui::ColorPicker4("Color", glm::value_ptr(color));
		ImGui::End();

		ImGui::Begin("CameraSpeed Customizer");
		ImGui::SliderFloat("CameraSpeed", &cameraSpeed, 0.0f, 15.0f);
		ImGui::End();
	}

	void onEvent(Cloud::Event& event) override {
		switch(event.getEventType()) {
			case Cloud::EventType::MOUSE_POSITION_CHANGED: {
				Cloud::MousePositionChangedEvent& e = (Cloud::MousePositionChangedEvent&)event;
				if(firstMouse) {
					lastMouseXPos = e.getX();
					lastMouseYPos = e.getY();
					firstMouse = false;
				}
				rotation.x = e.getX() - lastMouseXPos;
				rotation.y = e.getY() - lastMouseYPos;

				lastMouseXPos = e.getX();
				lastMouseYPos = e.getY();
			}
			case Cloud::EventType::KEY_PRESSED: {
				Cloud::KeyPressedEvent& e = (Cloud::KeyPressedEvent&)event;
				switch (e.getKeyCode()) {
					case KEY_W:			   input =  forward; break;
					case KEY_A:			   input = -right;	 break;
					case KEY_S:			   input = -forward; break;
					case KEY_D:			   input =  right;	 break;
					case KEY_SPACE:		   input =  up;		 break;
					case KEY_LEFT_CONTROL: input = -up;		 break;
					case KEY_Q:			   inputRotation =  1.0f; break;
					case KEY_E:			   inputRotation = -1.0f; break;
				}
			} break;
			case Cloud::EventType::KEY_RELEASED: {
				Cloud::KeyReleasedEvent& e = (Cloud::KeyReleasedEvent&)event;
				switch (e.getKeyCode()) {
					case KEY_W:			   input = glm::vec3(0,0,0); break;
					case KEY_A:			   input = glm::vec3(0,0,0); break;
					case KEY_S:			   input = glm::vec3(0,0,0); break;
					case KEY_D:			   input = glm::vec3(0,0,0); break;
					case KEY_SPACE:		   input = glm::vec3(0,0,0); break;
					case KEY_LEFT_CONTROL: input = glm::vec3(0,0,0); break;
					case KEY_Q:			   inputRotation = 0.0f; break;
					case KEY_E:			   inputRotation = 0.0f; break;
				}
				}
			}
		}
private:
	std::string name;

	std::shared_ptr<Cloud::Shader> shader;
	std::shared_ptr<Cloud::VertexBuffer> vertexBuffer;
	std::shared_ptr<Cloud::VertexArray> vertexArray;
	std::shared_ptr<Cloud::IndexBuffer> indexBuffer;

	Cloud::PerspectiveCamera camera;

	std::pair<float, float> playerInput;
	glm::vec3 input = glm::vec3(0, 0, 0);
	float inputRotation = 0;
	
	bool firstMouse = true;
	float lastMouseXPos = 0;
	float lastMouseYPos = 0;
	glm::vec3 rotation = glm::vec3(0, 0, 0);

	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	float brightness = 1.0f;
	float speed = 1.0;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	float cameraSpeed = 1.0f;
};


class App : public Cloud::Application {
public:
	App() {
		pushLayer(new ExampleLayer("Application"));
	}

	virtual ~App() {
	}
};

Cloud::Application* Cloud::createApplication() {
	return new App();
}