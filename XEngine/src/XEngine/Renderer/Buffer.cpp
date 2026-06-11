#include "xepch.h"
#include"Buffer.h"
#include "RendererAPI.h"											// For choosing suitable API

#include "Plantform/OpenGL/OpenGLBuffer.h"						// For using subclass's constructor which is wrote by an API you want to
//#include "Plantform/DirectX/DirtectXBuffer.h"					// So that initialize buffer as you liked

namespace XEngine{
	//////////////////////////////////////////////////////
	/////////////////// VertexBuffer /////////////////////
	//////////////////////////////////////////////////////
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: X_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported! ")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::API::DirectX: X_CORE_ASSERT(false, "RendererAPI::API::DirectX is currently not supported! ")
			return nullptr;
		}

		X_CORE_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}
	//////////////////////////////////////////////////////
	/////////////////// IndexBuffer //////////////////////
	//////////////////////////////////////////////////////


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: X_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported! ")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::API::DirectX: X_CORE_ASSERT(false, "RendererAPI::API::DirectX is currently not supported! ")
			return nullptr;
		}

		X_CORE_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}
}