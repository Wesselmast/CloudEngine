#pragma once

#include "RenderCommand.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "Shader.h"

namespace Cloud {
	class Renderer {
	public:
		static void beginScene(PerspectiveCamera& camera);
		static void endScene();

		static void submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		
		inline static RendererAPI::API getCurrentAPI() { 
			return RendererAPI::getAPI();
		}
	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* sceneData;
	};
}
