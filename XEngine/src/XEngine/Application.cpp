#include "xepch.h"

#include "Application.h"
#include <glad/glad.h>

#include"Input.h"

namespace XEngine
{
	Application* Application::s_Instance = nullptr;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		X_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));


		//X_CORE_TRACE("{0}", e);

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin(); )				//图层的事件处理是反向的（从尾到头）
		{
			(*--iter)->OnEvent(e);														//从最后一个迭代器所指的元素开始，逐个逆向相应事件
			if (e.Handled)																//如果在OnEvent中成功进行处理并将Handled变为true，则跳出循环
			{
				break;
			}
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)				//更新图层
			{
				layer->OnUpdate();
			}
			/*auto [x, y] = Input::GetMousePosition();
			X_CORE_TRACE("{0},{1}", x, y);*/
			m_Window->OnUpdate();							//更新窗口
		}
	}
}