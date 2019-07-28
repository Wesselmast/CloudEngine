#pragma once

namespace Cloud {

	class Shader {
	public:
		Shader(const char* &vertexSrc, const char* &pixelSrc);

		void bind() const;
		void unbind() const;

		~Shader();
	private:
		unsigned int compileShader(unsigned int type, const char* source);
	private:
		unsigned int rendererID;
	};
}