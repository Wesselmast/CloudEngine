#pragma once

#include "Cloud/Rendering/Shader.h"

namespace Cloud {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const char *& vertexSrc, const char *& pixelSrc);

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual int getUniformLocation(const char * name) const override;
		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
		virtual void uploadUniformF1(const std::string& name, const float& value) const override;
		virtual void uploadUniformVec4(const std::string& name, const glm::vec4& vector) const override;

		~OpenGLShader();
	private:
		unsigned int compileShader(unsigned int type, const char* source);
	private:
		unsigned int rendererID;
	};
}