#pragma once

#include "Cloud/Rendering/Renderer.h"
#include "Cloud/Rendering/Buffers/BufferLayout.h"

namespace Cloud {
	class Buffer {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual ~Buffer() {}
	};
}
