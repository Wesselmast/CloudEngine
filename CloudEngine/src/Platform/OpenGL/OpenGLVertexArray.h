#pragma once

#include "Cloud/Rendering/VertexArray.h"

namespace Cloud {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override {
			return vertexBuffers;
		}
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override {
			return indexBuffer;
			
		}
		
		~OpenGLVertexArray();
	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
		unsigned int rendererID;
	};
}
