#pragma once

#include "cldpch.h"

namespace Cloud {
	enum class ShaderDataType : uint8_t {
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		MAT3, MAT4,
		INT, INT2, INT3, INT4,
		BOOL
	};

	static uint8_t shaderDataTypeSize(ShaderDataType dataType) {
		switch (dataType) {
		case ShaderDataType::FLOAT:  return 4;
		case ShaderDataType::FLOAT2: return 8;
		case ShaderDataType::FLOAT3: return 12;
		case ShaderDataType::FLOAT4: return 16;
		case ShaderDataType::MAT3:   return 36;
		case ShaderDataType::MAT4:	 return 64;
		case ShaderDataType::INT:	 return 4;
		case ShaderDataType::INT2:	 return 8;
		case ShaderDataType::INT3:	 return 12;
		case ShaderDataType::INT4:	 return 16;
		case ShaderDataType::BOOL:	 return 1;
		}

		CLD_CORE_ASSERT(false, "Unknown shader data type");
		return 0;
	}

	struct BufferElement {
		ShaderDataType dataType;
		std::string name;
		bool normalized;
		uint8_t size;
		unsigned int offset;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
			dataType(type), name(name), normalized(normalized), size(shaderDataTypeSize(type)), offset(0) {
		}

		uint8_t getComponentCount() const {
			switch (dataType) {
			case ShaderDataType::FLOAT:  return 1;
			case ShaderDataType::FLOAT2: return 2;
			case ShaderDataType::FLOAT3: return 3;
			case ShaderDataType::FLOAT4: return 4;
			case ShaderDataType::MAT3:   return 9;
			case ShaderDataType::MAT4:	 return 16;
			case ShaderDataType::INT:	 return 1;
			case ShaderDataType::INT2:	 return 2;
			case ShaderDataType::INT3:	 return 3;
			case ShaderDataType::INT4:	 return 4;
			case ShaderDataType::BOOL:	 return 1;
			}
			CLD_CORE_ASSERT(false, "Unknown shader data type");
			return 0;
		}
	};

	typedef std::vector<BufferElement>::const_iterator BufferIterator;

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) :
			elements(elements) {
			calculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& getElements() const { return elements; }
		inline unsigned int getStride() const { return stride; }
		inline unsigned int length() const { return elements.size(); }

		BufferIterator begin() const { return elements.begin(); }
		BufferIterator end() const { return elements.end(); }

	private:
		void calculateOffsetsAndStride() {
			unsigned int offset = 0;
			stride = 0;
			for (auto& e : elements) {
				e.offset = offset;
				offset += e.size;
				stride += e.size;
			}
		}
	private:
		std::vector<BufferElement> elements;
		unsigned int stride = 0;
	};
	
}