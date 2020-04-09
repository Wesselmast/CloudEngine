#pragma once

#include "Cloud/Rendering/Buffers/IndexBuffer.h"

namespace Cloud {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(const void* indices, unsigned int count);

		virtual inline unsigned int getCount() const override { 
			return count; 
		}

		virtual void bind() const override;
		virtual void unbind() const override;

		~OpenGLIndexBuffer();
	private:
		unsigned int rendererID;
		unsigned int count;
	};
}
