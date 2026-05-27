#include <XEngine.h>

class ExampleLayer :public XEngine::Layer {
public:
	ExampleLayer():Layer("Example")
	{

	}

	void OnUpdate() override{
		
	}
	void OnEvent(XEngine::Event& event) override {
		X_TRACE("{0}",event);
	}
};

class Sandbox : public XEngine::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new XEngine::ImguiLayer());
		
	}
	~Sandbox() {}           
};

XEngine::Application* XEngine::CreateApplication()
{
	return new Sandbox();
}