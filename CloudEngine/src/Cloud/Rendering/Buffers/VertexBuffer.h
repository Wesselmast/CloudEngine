#pragma once
#include "Buffer.h"

#include "BufferLayout.h"

namespace Cloud {
	class VertexBuffer : public Buffer {
	public:
		static VertexBuffer* create(const void* vertices, unsigned int size);

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& bufferLayout) = 0;
	};
}