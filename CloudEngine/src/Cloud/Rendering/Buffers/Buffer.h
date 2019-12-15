#pragma once

namespace Cloud {
	class Buffer {
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual ~Buffer() {}
	};
}
