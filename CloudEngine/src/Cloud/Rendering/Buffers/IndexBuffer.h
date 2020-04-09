#pragma once
#include "Buffer.h"

namespace Cloud {
	class IndexBuffer : public Buffer {
	public:
		virtual inline unsigned int getCount() const = 0;
		static IndexBuffer* create(const void* indices, unsigned int count);
	};
}