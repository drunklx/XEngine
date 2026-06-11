#pragma once
#include "Core.h"

#include "Window.h"
#include "XEngine/LayerStack.h"
#include "Imgui/ImguiLayer.h"
#include "XEngine/Events/ApplicationEvent.h"
//Temp
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/Buffer.h"
#include "XEngine/Renderer/VertexArray.h"
namespace XEngine
{
	class X_API Application  
		{
	
		
		public:

			Application();
			virtual ~Application();
			
			void Run();
			
			void OnEvent(Event& e);
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
			inline Window& GetWindow() { return *m_Window; }
			inline static Application& Get() { return *s_Instance; }

		private:
			bool OnWindowClose(WindowCloseEvent& e);

			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			ImguiLayer* m_ImguiLayer;
			LayerStack m_LayerStack;

			std::shared_ptr<Shader> m_Shader;
			std::shared_ptr<VertexArray> m_VertexArray;


			std::shared_ptr<Shader> blueShader;
			std::shared_ptr<VertexArray> squVAO;

		private:
			static Application* s_Instance;
		};
		

	// To be defined in client
	Application* CreateApplication();

}


