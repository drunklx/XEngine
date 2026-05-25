#pragma once
#include "Core.h"

#include "Window.h"
#include "XEngine/Events/ApplicationEvent.h"
namespace XEngine
{
	class X_API Application  
		{
	
		public:

			Application();
			virtual ~Application();
			
			void Run();
			
			void OnEvent(Event& e);
			bool OnWindowClose(WindowCloseEvent& e);

		private:
			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
		};
		

	// To be defined in client
	Application* CreateApplication();

}


