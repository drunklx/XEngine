#include "xepch.h"

#include "Application.h"
#include "Renderer/Renderer.h"

#include"Input.h"

namespace XEngine
{
	Application* Application::s_Instance = nullptr;

	

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
		:m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		X_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);
		
		m_VertexArray.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{	// when we set the layout, we store the layout data in OpenGLBuffer.m_Layout by "SetLayout()" function, then delete layout.
			BufferLayout layout =
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		uint32_t indices[3] = {
			0,1,2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			in vec3 v_Position;
			in vec4 v_Color;
			layout(location = 0) out vec4 a_Color;

			void main()
			{
				a_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
				a_Color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		float squV[4 * 3] = {
			-0.75, -0.75f,	-0.1f,
			0.75f, -0.75f,	-0.1f,
			0.75f,	0.75f,	-0.1f,
			-0.75f,	0.75f,	-0.1f
		};

		unsigned int squI[6] = {
			0,1,2,
			2,3,0
		};
		squVAO.reset(VertexArray::Create());
		BufferLayout squLayout =
		{
			{ ShaderDataType::Float3, "a_Position" }
		};
		std::shared_ptr<VertexBuffer> blueVB(VertexBuffer::Create(squV, sizeof(squV)));
		blueVB->SetLayout(squLayout);
		squVAO->AddVertexBuffer(blueVB);
		

		squVAO->SetIndexBuffer(std::shared_ptr<IndexBuffer>(IndexBuffer::Create(squI, sizeof(squI) / sizeof(uint32_t))));
		std::string blueVSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position =  u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string blueFSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 a_Color;

			void main()
			{
				a_Color = vec4(0.0,0.0,1.0,1.0);
			}
		)";
		blueShader.reset(new Shader(blueVSrc, blueFSrc));

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
			RendererCommand::Clear();
			RendererCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });
			Renderer::BeginScene(m_Camera);
			Renderer::Submit(blueShader,std::shared_ptr<VertexArray>(squVAO));
			Renderer::Submit(m_Shader,m_VertexArray);
			Renderer::EndScene();

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