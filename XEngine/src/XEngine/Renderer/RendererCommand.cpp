#include "xepch.h"
#include "RendererCommand.h"

#include "Plantform/OpenGL/OpenGLRendererAPI.h"

namespace XEngine
{
	RendererAPI* RendererAPI::Create() {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: X_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLRendererAPI();
		case RendererAPI::API::DirectX: X_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
			return nullptr;
		}
		X_CORE_ASSERT(false, "Unknown Renderer API!")
			return nullptr;
	}

	RendererAPI* RendererCommand::s_RendererAPI = RendererAPI::Create();


	//RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;


}