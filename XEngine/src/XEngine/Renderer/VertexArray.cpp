#include "xepch.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Plantform/OpenGL/OpenGLVertexArray.h"

namespace XEngine {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: X_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		case RendererAPI::API::DirectX: X_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
			return nullptr;
		}

		X_CORE_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}
}