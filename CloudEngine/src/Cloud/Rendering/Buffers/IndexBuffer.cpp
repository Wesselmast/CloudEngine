#include "cldpch.h"

#include "IndexBuffer.h"

#include "Platform/OpenGL/Buffers/OpenGLIndexBuffer.h"
#include "Cloud/Rendering/Renderer.h"


namespace Cloud {
	IndexBuffer* IndexBuffer::create(const void* indices, unsigned int count) {
		switch (Renderer::getCurrentAPI()) {
		case RendererAPI::API::NONE:
		{
			CLD_CORE_ASSERT(false, "API is NONE");
			return nullptr;
		}
		case RendererAPI::API::OPENGL:
		{
			return new OpenGLIndexBuffer(indices, count);
		}
		}
		CLD_CORE_ASSERT(false, "API is unknown");
		return nullptr;
	}
}
