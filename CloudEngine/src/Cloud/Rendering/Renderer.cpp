#include "cldpch.h"
#include "Renderer.h"

namespace Cloud {
	Renderer::SceneData* Renderer::sceneData = new SceneData;
	
	//makes sure the shaders I have get the right uniforms
	void Renderer::beginScene(PerspectiveCamera& camera) {
		sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene() {
	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->bind();
		shader->uploadUniformMat4("uViewProjection", sceneData->viewProjectionMatrix);
		shader->uploadUniformMat4("uTransform", transform);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}