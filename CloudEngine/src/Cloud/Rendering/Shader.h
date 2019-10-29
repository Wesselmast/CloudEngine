#pragma once

namespace Cloud {
	class Shader {
	public:
		static Shader* create(const char *& vertexSrc, const char *& pixelSrc);
			
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual int getUniformLocation(const char* name) const = 0;

		virtual ~Shader() {}
	private:
		unsigned int rendererID;
	};
}