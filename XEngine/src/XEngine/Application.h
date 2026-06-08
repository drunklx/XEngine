#pragma once
#include "Core.h"

#include "Window.h"
#include "XEngine/LayerStack.h"
#include "Imgui/ImguiLayer.h"
#include "XEngine/Events/ApplicationEvent.h"
//Temp
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/Buffer.h"
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

			std::unique_ptr<Shader> m_Shader;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;

		private:
			static Application* s_Instance;
			unsigned int m_VertexArray;
		};
		

	// To be defined in client
	Application* CreateApplication();

}


