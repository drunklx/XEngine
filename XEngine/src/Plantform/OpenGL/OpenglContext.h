#pragma once
#include "XEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;												// Avoid reporting errors & Don't need include GLFW header file

namespace XEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}