#pragma once
#include "Cloud/Rendering/RendererAPI.h"


namespace Cloud {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		void clear(const glm::vec4& color) override;
		void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		void drawIndexedMesh(const std::shared_ptr<Mesh>& mesh) override;
	};
	
}