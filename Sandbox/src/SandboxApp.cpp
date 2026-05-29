#include <XEngine.h>

class ExampleLayer :public XEngine::Layer {
public:
	ExampleLayer():Layer("Example")
	{

	}

	void OnUpdate() override {
		//X_TRACE("ExampleLayer::OnUpdate");
	}
	void OnEvent(XEngine::Event& event) override {
		if (event.GetEventType() == XEngine::EventType::KeyPressed) {
			XEngine::KeyPressedEvent& e = (XEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == X_KEY_TAB)
				X_TRACE("{0} is pressed", "Tab");
			X_TRACE("{0} is pressed", (char)e.GetKeyCode());
		}
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