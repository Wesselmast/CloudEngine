#include "cldpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Cloud {
	Shader* Shader::create(const char *& vertexSrc, const char *& pixelSrc) {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::NONE:
		{
			CLD_CORE_ASSERT(false, "RendererAPI is NONE");
			return nullptr;
		}
		case RendererAPI::OPENGL:
		{
			return new OpenGLShader(vertexSrc, pixelSrc);
		}
		}
		CLD_CORE_ASSERT(false, "RendererAPI is unknown");
		return nullptr;
	}
}