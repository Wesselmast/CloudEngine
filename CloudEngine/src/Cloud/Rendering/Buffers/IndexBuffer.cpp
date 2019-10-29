#include "cldpch.h"

#include "IndexBuffer.h"

#include "Platform/OpenGL/Buffers/OpenGLIndexBuffer.h"

namespace Cloud {
	IndexBuffer* IndexBuffer::create(unsigned int* indices, unsigned int count) {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::NONE:
		{
			CLD_CORE_ASSERT(false, "RendererAPI is NONE");
			return nullptr;
		}
		case RendererAPI::OPENGL:
		{
			return new OpenGLIndexBuffer(indices, count);
		}
		}
		CLD_CORE_ASSERT(false, "RendererAPI is unknown");
		return nullptr;
	}
}
