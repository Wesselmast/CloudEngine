#include "cldpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cloud {
	VertexArray * VertexArray::create() {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::NONE:
		{
			CLD_CORE_ASSERT(false, "RendererAPI is NONE");
			return nullptr;
		}
		case RendererAPI::OPENGL:
		{
			return new OpenGLVertexArray();
		}
		}
		CLD_CORE_ASSERT(false, "RendererAPI is unknown");
		return nullptr;
	}
}