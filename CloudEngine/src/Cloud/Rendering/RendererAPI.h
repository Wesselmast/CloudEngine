#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Cloud {
	struct Mesh {
	public:
		uint32_t baseVertex = 0;
		uint32_t baseIndex = 0;
		uint32_t indexCount = 0;
		glm::mat4 transform = glm::mat4(1.0f);
	};
	
	class RendererAPI {
	public:
		virtual ~RendererAPI() = default;

		enum class API {
			NONE, OPENGL
		};
	public:
		virtual void clear(const glm::vec4& color) = 0;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void drawIndexedMesh(const std::shared_ptr<Mesh>& mesh) = 0;

		inline static API getAPI() {
			return api;
		}
	private:
		static API api;
	};
}
