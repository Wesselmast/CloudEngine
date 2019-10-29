#pragma once

namespace Cloud {
	enum class RendererAPI {
		NONE, OPENGL
	};

	class Renderer {
	public:
		inline static RendererAPI getCurrentAPI() { 
			return rendererAPI;
		}
	private:
		static RendererAPI rendererAPI;
	};
}