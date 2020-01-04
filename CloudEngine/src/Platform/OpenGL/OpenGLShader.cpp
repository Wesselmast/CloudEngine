#include "cldpch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"

#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <sstream>

namespace Cloud {

	OpenGLShader::OpenGLShader(const std::string& path) {
		const ShaderProgram program = OpenGLShader::parseShaderFile(path);

		unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, program.vertexSrc.c_str());
		unsigned int pixelShader = compileShader(GL_FRAGMENT_SHADER, program.pixelSrc.c_str());

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

	ShaderProgram OpenGLShader::parseShaderFile(const std::string& path) const {
		std::ifstream stream(path);

		enum class ShaderType {
			NONE	= -1,
			VERTEX	=  0,
			FRAG	=  1
		} type = ShaderType::NONE;

		std::string line;
		std::stringstream ss[2];
		while(getline(stream, line)) {
			if(line.find("#type") != std::string::npos) {
				if(line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				}
				else if (line.find("frag") != std::string::npos) {
					type = ShaderType::FRAG;
				}
			}
			else {
				if(type == ShaderType::NONE) {
					CLD_CORE_ASSERT(false, "Wrote code before defining the shader type!");
				}
				ss[(int)type] << line << '\n';
			}
		}
		return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAG].str() };
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const {
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformF1(const std::string& name, const float& value) const {
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformF4(const std::string& name, const glm::vec4& vector) const {
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(rendererID);
	}
}