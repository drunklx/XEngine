#pragma once
#include "Core.h"
namespace XEngine
{
	class X_API Application
		{
	
		public:

			Application();
			virtual ~Application();
			void Run();
		};

	// To be defined in client
	Application* CreateApplication();
}


