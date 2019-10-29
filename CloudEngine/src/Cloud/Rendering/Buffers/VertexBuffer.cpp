#include "cldpch.h"
	
#include "VertexBuffer.h"

#include "Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"

namespace Cloud {
	VertexBuffer* VertexBuffer::create(float* vertices, unsigned int size) {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::NONE:
		{
			CLD_CORE_ASSERT(false, "RendererAPI is NONE");
			return nullptr;
		}
		case RendererAPI::OPENGL:
		{
			return new OpenGLVertexBuffer(vertices, size);
		}
		}
		CLD_CORE_ASSERT(false, "RendererAPI is unknown");
		return nullptr;
	}
}
