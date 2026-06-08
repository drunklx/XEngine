#include "xepch.h"
#include"Buffer.h"
#include "Renderer.h"											// For choosing suitable API

#include "Plantform/OpenGL/OpenGLBuffer.h"						// For using subclass's constructor which is wrote by an API you want to
//#include "Plantform/DirectX/DirtectXBuffer.h"					// So that initialize buffer as you liked

namespace XEngine{
	//////////////////////////////////////////////////////
	/////////////////// VertexBuffer /////////////////////
	//////////////////////////////////////////////////////
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: X_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::DirectX: X_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
			return nullptr;
		}

		X_CORE_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}
	//////////////////////////////////////////////////////
	/////////////////// IndexBuffer //////////////////////
	//////////////////////////////////////////////////////


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: X_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::DirectX: X_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
			return nullptr;
		}

		X_CORE_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}
}