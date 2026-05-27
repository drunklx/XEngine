// 包含预编译头（加速编译）
#include "xepch.h"

// 包含窗口类的声明头文件
#include "WindowsWindow.h"

#include"XEngine/Events/ApplicationEvent.h"
#include "XEngine/Events/MouseEvent.h"
#include "XEngine/Events/KeyEvent.h"


namespace XEngine {

	// 静态变量：标记 GLFW 是否全局初始化过（只初始化一次）
	static bool S_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		X_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	// 构造函数：传入窗口属性（宽、高、标题），直接调用初始化
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	// 析构函数：窗口销毁时自动调用，关闭窗口
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	// 静态工厂方法：创建一个 Windows 窗口实例
	// 上层引擎调用 Window::Create() 即可创建窗口，不用关心平台
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}


	// 引擎每帧都会调用的更新函数
	void WindowsWindow::OnUpdate()
	{
		// 1. 轮询处理所有输入事件（键盘、鼠标、窗口事件）
		glfwPollEvents();
		// 2. 交换前后缓冲区，把渲染好的画面显示到屏幕
		glfwSwapBuffers(m_Window);
	}

	// 开启/关闭垂直同步（VSync）
	void WindowsWindow::SetVSync(bool enabled)
	{
		// glfwSwapInterval(1) 开启 VSync，0 关闭
		glfwSwapInterval(enabled ? 1 : 0);

		// 保存状态到窗口数据里
		m_Data.VSync = enabled;
	}

	// 获取 VSync 状态（这里写死返回 false，应该是待完善）
	bool WindowsWindow::IsVSync() const
	{
		return false;
	}


	// ==================== 窗口初始化核心函数 ====================
	void WindowsWindow::Init(const WindowProps& props)
	{
		// 把窗口标题、宽、高保存到 m_Data 结构体中
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// 打印日志：创建窗口
		X_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		// 如果 GLFW 还没初始化，就全局初始化一次
		if (!S_GLFWInitialized)
		{
			// 初始化 GLFW 库
			int success = glfwInit();
			// 如果初始化失败，直接断言崩溃并提示错误
			X_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			// 标记已初始化
			S_GLFWInitialized = true;
		}

		// 调用 GLFW 创建窗口，返回窗口句柄
		m_Window = glfwCreateWindow(
			(int)props.Width, (int)props.Height,  // 宽高
			m_Data.Title.c_str(),                 // 标题
			nullptr, nullptr                      // 全屏/共享上下文（不用）
		);
		
		// 将此窗口设置为当前 OpenGL 渲染上下文
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		X_CORE_ASSERT(status, "Failed to initialize Glad!");
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		// 关键：把 m_Data 指针绑定到 GLFW 窗口
		// 作用：事件回调时可以取回窗口数据（非常重要）
 		glfwSetWindowUserPointer(m_Window, &m_Data);

		// 默认开启垂直同步
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				// 通过窗口指针获取绑定的窗口数据
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				// 更新窗口数据中的宽高
				data.Width = width;
				data.Height = height;
				// 创建一个窗口大小改变事件，传入新的宽高
				WindowResizeEvent event(width, height);
				// 调用事件回调函数，传入事件对象
				data.EventCallback(event);
				
			});
			
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				// 通过窗口指针获取绑定的窗口数据
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				// 创建一个窗口关闭事件
				WindowCloseEvent event;
				// 调用事件回调函数，传入事件对象
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scanmode, int action, int mods) 
			{
				// 通过窗口指针获取绑定的窗口数据
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0, scanmode);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key,scanmode);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1, scanmode);
						data.EventCallback(event);
						break;
					}
					default:
						break;
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window,unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);

			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window,int button,int action,int modes) 
			{
				// 通过窗口指针获取绑定的窗口数据
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
					default:
						break;
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				// 通过窗口指针获取绑定的窗口数据
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				// 通过窗口指针获取绑定的窗口数据
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	// 关闭销毁窗口
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}