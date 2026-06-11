#pragma once
# include "XEngine/Renderer/RendererAPI.h"
namespace XEngine {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Clear() override;
		void SetClearColor(const glm::vec4& color) override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}

