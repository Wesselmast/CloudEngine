#include <CloudEngine.h>

#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"

#include "imgui/imgui.h"


static const uint32_t meshImportFlags =
		aiProcess_Triangulate |
		aiProcess_SortByPType |
		aiProcess_OptimizeMeshes |
		aiProcess_ValidateDataStructure;


class ExampleLayer : public Cloud::Layer {
public:
	ExampleLayer(const std::string& name = "Example") : Layer(name), name(name), camera(68.0f, 1600.0f/900.0f, 0.01f, 100.0f) {

		camera.setPosition({ 0, 0, 30 });
		
		/*	HEXAGON 2d
			0.75f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		   0.33f, -0.75f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		  -0.33f, -0.75f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
		  -0.75f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		   0.0f,   0.75f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f
		*/


		importer = std::make_unique<Assimp::Importer>();
		const aiScene* scene = importer->ReadFile("res/models/Cube.obj", meshImportFlags);

		CLD_CORE_ASSERT(scene && scene->HasMeshes(), "Scene doesn't contain meshes, failed to load mesh files");
		aiMesh* mesh = scene->mMeshes[0];

		std::vector<glm::vec3> vertices;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			vertices.push_back({ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		}
		
		subMesh.indexCount = mesh->mNumFaces * 3;
		
		std::vector<glm::vec3> indices;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			CLD_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "Faces must have three indices");
			indices.push_back({ mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] });
		}

		
		/*float vertices[] = {
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
		}; */

		vertexArray.reset(Cloud::VertexArray::create());
		vertexBuffer.reset(Cloud::VertexBuffer::create(vertices.data(), vertices.size()));
		//vertexBuffer.reset(Cloud::VertexBuffer::create(vertices, sizeof(vertices)));

		vertexBuffer->setLayout({
			{ Cloud::ShaderDataType::FLOAT3, "aPosition" }
		});
		vertexArray->addVertexBuffer(vertexBuffer);
		
		indexBuffer.reset(Cloud::IndexBuffer::create(indices.data(), indices.size() * sizeof(glm::vec3)));
		//indexBuffer.reset(Cloud::IndexBuffer::create(indices, sizeof(indices) * sizeof(unsigned int)));
		vertexArray->setIndexBuffer(indexBuffer);

		shader.reset(Cloud::Shader::create("res/shaders/Example.shader"));
	}
	
	void onUpdate(const double deltaTime, const double time) override {
		Cloud::RenderCommand::clear();
		camera.setRotation(camera.getRotation() + inputRotation * (float)deltaTime * sensitivity);
		inputRotation = glm::vec3(0, 0, 0);
		
		forward = normalize(
			glm::vec3(
				cos(glm::radians(camera.getRotation().x)) * cos(camera.getRotation().y),
				sin(camera.getRotation().y),
				sin(glm::radians(camera.getRotation().x)) * cos(camera.getRotation().y)
			)
		);
		right = normalize(cross(forward, glm::vec3(0, 1, 0)));
		up = normalize(cross(right, forward));
		
		camera.setPosition(camera.getPosition() + input * (float)deltaTime * cameraSpeed);
		
		Cloud::Renderer::beginScene(camera);
		{
			shader->uploadUniformF1("uRed", sin(time * speed) * 0.5 + brightness - 0.5);

			shader->uploadUniformF4("uColor", color);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
			//Cloud::Renderer::submit(vertexArray, shader, transform);
			Cloud::Renderer::submitMesh(vertexArray, shader, std::make_shared<Cloud::Mesh>(subMesh));

			//int halfSize = 5;
			//
			//for(int x = -halfSize; x < halfSize; x++) {
			//	for (int y = -halfSize; y < halfSize; y++) {
			//		for (int z = -halfSize; z < halfSize; z++) {
			//			glm::vec3 position(x * 0.25f, y* 0.25f, z* 0.25f);
			//			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			//			if (x % 2 == 0) {
			//				shader->uploadUniformF4("uColor", color);
			//			}
			//			else {
			//				shader->uploadUniformF4("uColor", color2);
			//			}
			//			Cloud::Renderer::submit(vertexArray, shader, transform);
			//		}
			//	}
			//}
		}
		Cloud::Renderer::endScene();
	}

	void onImGuiRender() override {
		ImGui::Begin("Shape Customizer");
		ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);
		ImGui::SliderFloat("Speed", &speed, 0.0f, 15.0f);
		ImGui::ColorPicker4("Color", glm::value_ptr(color));
		ImGui::ColorPicker4("Color2", glm::value_ptr(color2));
		ImGui::End();

		ImGui::Begin("Camera Customizer");
		ImGui::SliderFloat("Speed", &cameraSpeed, 0.0f, 15.0f);
		ImGui::SliderFloat("Sensitivity", &sensitivity, 0.0f, 10.0f);
		ImGui::End();
	}

	void onEvent(Cloud::Event& event) override {
		switch(event.getEventType()) {
			case Cloud::EventType::MOUSE_POSITION_CHANGED: {
				Cloud::MousePositionChangedEvent& e = (Cloud::MousePositionChangedEvent&)event;
				if (enableCameraRotation) {
					if (firstMouse) {
						lastMouseXPos = e.getX();
						lastMouseYPos = e.getY();
						firstMouse = false;
					}
					inputRotation.x = e.getX() - lastMouseXPos;
					inputRotation.y = e.getY() - lastMouseYPos;

					lastMouseXPos = e.getX();
					lastMouseYPos = e.getY();
				}
			}
			case Cloud::EventType::MOUSE_BUTTON_PRESSED: {
				Cloud::MouseButtonPressedEvent& e = (Cloud::MouseButtonPressedEvent&)event;
				if (e.getMouseButton() == MOUSE_BTN_2) {
					enableCameraRotation = true;
				}
			} break;
			case Cloud::EventType::MOUSE_BUTTON_RELEASED: {
				Cloud::MouseButtonReleasedEvent& e = (Cloud::MouseButtonReleasedEvent&)event;
				if(e.getMouseButton() == MOUSE_BTN_2) {
					enableCameraRotation = false;
					firstMouse = true;
				}
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
				}
			} break;
			case Cloud::EventType::KEY_RELEASED: {
				Cloud::KeyReleasedEvent& e = (Cloud::KeyReleasedEvent&)event;
				switch (e.getKeyCode()) {
					case KEY_W:			   input = glm::vec3(0.0f); break;
					case KEY_A:			   input = glm::vec3(0.0f); break;
					case KEY_S:			   input = glm::vec3(0.0f); break;
					case KEY_D:			   input = glm::vec3(0.0f); break;
					case KEY_SPACE:		   input = glm::vec3(0.0f); break;
					case KEY_LEFT_CONTROL: input = glm::vec3(0.0f); break;
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
	Cloud::Mesh subMesh;

	Cloud::PerspectiveCamera camera;

	std::pair<float, float> playerInput;
	glm::vec3 input = glm::vec3(0, 0, 0);
	
	bool firstMouse = true;
	float lastMouseXPos = 0;
	float lastMouseYPos = 0;
	glm::vec3 inputRotation = glm::vec3(0, 0, 0);

	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	float brightness = 1.0f;
	float speed = 1.0;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 color2 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	float cameraSpeed = 1.0f;
	float sensitivity = 0.2f;

	std::unique_ptr<Assimp::Importer> importer;
	bool enableCameraRotation = false;
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