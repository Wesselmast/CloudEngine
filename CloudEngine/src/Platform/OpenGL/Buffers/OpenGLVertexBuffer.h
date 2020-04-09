#pragma once

#include "Cloud/Rendering/Buffers/VertexBuffer.h"

namespace Cloud {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(const void* vertices, unsigned int size);

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual inline const BufferLayout& getLayout() const override {
			return layout;
		}

		virtual inline void setLayout(const BufferLayout& bufferLayout) override {
			layout = bufferLayout;
		}

		~OpenGLVertexBuffer();
	private:
		unsigned int rendererID;
		BufferLayout layout;
	};
}
