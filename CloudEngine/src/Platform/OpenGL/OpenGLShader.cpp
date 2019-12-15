#include "cldpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

namespace Cloud {

	OpenGLShader::OpenGLShader(const char *& vertexSrc, const char *& pixelSrc) {
		unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int pixelShader = compileShader(GL_FRAGMENT_SHADER, pixelSrc);

		rendererID = glCreateProgram();

		glAttachShader(rendererID, vertexShader);
		glAttachShader(rendererID, pixelShader);

		glLinkProgram(rendererID);

		int isLinked = 0;
		glGetProgramiv(rendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			int maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(rendererID);
			glDeleteShader(pixelShader);
			glDeleteShader(vertexShader);

			CLD_CORE_ERROR("{0}", infoLog.data());
			CLD_CORE_ASSERT(false, "Shader failed linking");
			return;
		}

		glDetachShader(rendererID, vertexShader);
		glDetachShader(rendererID, pixelShader);
	}

	void OpenGLShader::bind() const {
		glUseProgram(rendererID);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(0);
	}

	unsigned int OpenGLShader::compileShader(unsigned int type, const char * source) {
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			int maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			CLD_CORE_ERROR("{0}", infoLog.data());
			switch (type) {
			case GL_VERTEX_SHADER:   CLD_CORE_ASSERT(false, "Vertex shader failed compiling");
			case GL_FRAGMENT_SHADER: CLD_CORE_ASSERT(false, "Pixel shader failed compiling");
			}

			return shader;
		}
		return shader;
	}

	int OpenGLShader::getUniformLocation(const char * name) const {
		return glGetUniformLocation(rendererID, "uRed");
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const {
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformF1(const std::string& name, const float& value) const {
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformVec4(const std::string& name, const glm::vec4& vector) const {
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(rendererID);
	}
}