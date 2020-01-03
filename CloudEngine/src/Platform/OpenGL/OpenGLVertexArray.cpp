#include "cldpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Cloud {
	static GLenum shaderDataTypeToGLenum(const ShaderDataType& dataType) {
		switch (dataType) {
			case ShaderDataType::FLOAT:  return GL_FLOAT;
			case ShaderDataType::FLOAT2: return GL_FLOAT;
			case ShaderDataType::FLOAT3: return GL_FLOAT;
			case ShaderDataType::FLOAT4: return GL_FLOAT;
			case ShaderDataType::MAT3:   return GL_FLOAT;
			case ShaderDataType::MAT4:	 return GL_FLOAT;
			case ShaderDataType::INT:	 return GL_INT;
			case ShaderDataType::INT2:	 return GL_INT;
			case ShaderDataType::INT3:	 return GL_INT;
			case ShaderDataType::INT4:	 return GL_INT;
			case ShaderDataType::BOOL:	 return GL_BOOL;
		}
		CLD_CORE_ASSERT(false, "Unknown shader data type");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &rendererID);
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		CLD_CORE_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "Tried to add vertex buffer without a layout");
		
		glBindVertexArray(rendererID);
		vertexBuffer->bind();

		unsigned int index = 0;
		const BufferLayout& layout = vertexBuffer->getLayout();
		
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.getComponentCount(),
				shaderDataTypeToGLenum(element.dataType),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset);
			index++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(rendererID);
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &rendererID);
	}
}