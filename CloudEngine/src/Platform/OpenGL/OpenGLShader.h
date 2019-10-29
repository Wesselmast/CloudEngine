#pragma once

#include "Cloud/Rendering/Shader.h"

namespace Cloud {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const char *& vertexSrc, const char *& pixelSrc);

		virtual void bind() const;
		virtual void unbind() const;
		virtual int getUniformLocation(const char * name) const;

		~OpenGLShader();
	private:
		unsigned int compileShader(unsigned int type, const char* source);
	private:
		unsigned int rendererID;
	};
}