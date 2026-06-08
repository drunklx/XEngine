#include "xepch.h"

#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);
		
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);


		float vertices[3 * 3] = {
			-0.5f, -0.5f,   0.0f,
			0.5f,  -0.5f,	0.0f,
			0.0f,	0.5f,	0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

		uint32_t indices[3] = {
			0,1,2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				v_Position = a_Position;
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 a_Color;
			in vec3 v_Position;
			
			void main()
			{
				a_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

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
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES,m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)				//更新图层
			{
				layer->OnUpdate();
			}
			/*auto [x, y] = Input::GetMousePosition();
			X_CORE_TRACE("{0},{1}", x, y);*/

			m_ImguiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();						
			m_ImguiLayer->End();

			m_Window->OnUpdate();							//更新窗口
		}
	}
}