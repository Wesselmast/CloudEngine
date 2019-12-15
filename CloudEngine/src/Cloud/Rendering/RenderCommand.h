#pragma once

#include "RendererAPI.h"

namespace Cloud {
	class RenderCommand {
	public:
		inline static void clear(const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) {
			api->clear(color);
		}
		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			api->drawIndexed(vertexArray);
		}
	private:
		static RendererAPI* api;
	};
	
}