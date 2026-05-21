#pragma once

#ifdef X_PLATFORM_WINDOWS

extern XEngine::Application* XEngine::CreateApplication();

int main(int argc, char** argv)
{
	XEngine::Log::Init();
	X_CORE_WARN("Initialized Log!");
	int a = 5;
	X_INFO("Hello! Var={0}", a);

	auto app = XEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif