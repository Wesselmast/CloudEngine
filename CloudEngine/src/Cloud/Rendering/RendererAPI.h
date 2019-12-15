#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Cloud {
	class RendererAPI {
	public:
		enum class API {
			NONE, OPENGL
		};
	public:
		virtual void clear(const glm::vec4& color) = 0;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API getAPI() {
			return api;
		}
	private:
		static API api;
	};
}
