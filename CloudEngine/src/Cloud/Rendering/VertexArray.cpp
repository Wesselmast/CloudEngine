#include "cldpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cloud {
	VertexArray * VertexArray::create() {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::API::NONE:
		{
			CLD_CORE_ASSERT(false, "API is NONE");
			return nullptr;
		}
		case RendererAPI::API::OPENGL:
		{
			return new OpenGLVertexArray();
		}
		}
		CLD_CORE_ASSERT(false, "API is unknown");
		return nullptr;
	}
}