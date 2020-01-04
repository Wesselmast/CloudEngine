#include "cldpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cloud {
	Shader* Shader::create(const std::string& path) {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::API::NONE:
		{
			CLD_CORE_ASSERT(false, "API is NONE");
			return nullptr;
		}
		case RendererAPI::API::OPENGL:
		{
			return new OpenGLShader(path);
		}
		}
		CLD_CORE_ASSERT(false, "API is unknown");
		return nullptr;
	}
}
