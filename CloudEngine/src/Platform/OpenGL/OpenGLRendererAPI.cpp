#include "cldpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Cloud {
	void OpenGLRendererAPI::clear(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::drawIndexedMesh(const std::shared_ptr<Mesh>& mesh) {
		glDrawElementsBaseVertex(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * mesh->baseIndex), mesh->baseVertex);
	}
}
