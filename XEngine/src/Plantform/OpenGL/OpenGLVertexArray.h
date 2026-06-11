#pragma once
#include "XEngine/Renderer/VertexArray.h"
namespace XEngine {
	class OpenGLVertexArray :
		public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr< IndexBuffer>& indexbuffer) override;

		virtual const std::vector<std::shared_ptr< VertexBuffer>> &GetVertexBuffer()const override;
		virtual const std::shared_ptr< IndexBuffer> &GetIndexBuffer()const override;
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;	//一个 VAO 可以绑定多个 VBO
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}
