#include "cldpch.h"
	
#include "VertexBuffer.h"

#include "Platform/OpenGL/Buffers/OpenGLVertexBuffer.h"
#include "Cloud/Rendering/Renderer.h"

namespace Cloud {
	VertexBuffer* VertexBuffer::create(float* vertices, unsigned int size) {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::API::NONE:
		{
			CLD_CORE_ASSERT(false, "API is NONE");
			return nullptr;
		}
		case RendererAPI::API::OPENGL:
		{
			return new OpenGLVertexBuffer(vertices, size);
		}
		}
		CLD_CORE_ASSERT(false, "API is unknown");
		return nullptr;
	}
}
