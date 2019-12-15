#pragma once

#include "glm/glm.hpp"

namespace Cloud {
	class Shader {
	public:
		static Shader* create(const char *& vertexSrc, const char *& pixelSrc);
			
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual int getUniformLocation(const char* name) const = 0;
		
		virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;
		virtual void uploadUniformF1(const std::string& name, const float& value) const = 0;
		virtual void uploadUniformVec4(const std::string& name, const glm::vec4& vector) const = 0;

		virtual ~Shader() {}
	private:
		unsigned int rendererID;
	};
}