#pragma once
#include "Buffer.h"

namespace Cloud {
	class VertexBuffer : public Buffer {
	public:
		static VertexBuffer* create(float* vertices, unsigned int size);

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& bufferLayout) = 0;
	};
}