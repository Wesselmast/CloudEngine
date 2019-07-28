#pragma once

namespace Cloud {
	class Context {
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
}