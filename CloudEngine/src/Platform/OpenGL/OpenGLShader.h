#pragma once

#include "Cloud/Rendering/Shader.h"

namespace Cloud {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual int getUniformLocation(const char * name) const override;

		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;
		virtual void uploadUniformF1(const std::string& name, const float& value) const override;
		virtual void uploadUniformF4(const std::string& name, const glm::vec4& vector) const override;

		~OpenGLShader();
	protected:
		virtual ShaderProgram parseShaderFile(const std::string& path) const override;
	private:
		unsigned int compileShader(unsigned int type, const char* source);
	private:
		unsigned int rendererID;
	};
}