#include <xepch.h>

#include "Core.h"
#include "Events/Event.h"

namespace XEngine {

	struct WindowProps
	{
		std::string Title; // 窗口标题
		unsigned int Width; // 窗口宽度
		unsigned int Height; // 窗口高度
		// 构造函数，提供默认值
		WindowProps(const std::string& title = "XEngine Window",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};
	// 窗口类，封装了窗口的创建、更新和事件处理
	class X_API Window
	{
	public:
		// 定义一个函数指针类型，用于事件回调
		using EventCallbackFn= std::function<void(Event&)>;
		// 析构函数，释放窗口资源
		virtual ~Window() {}
		// 更新窗口状态（如交换缓冲区、处理事件等）
		virtual void OnUpdate() = 0;
		// 获取窗口宽度
		virtual unsigned int GetWidth() const = 0;
		// 获取窗口高度
		virtual unsigned int GetHeight() const = 0;
		// 设置事件回调函数，当窗口事件发生时调用
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		// 设置垂直同步（VSync）开关，开启后帧率与显示器刷新率同步
		virtual void SetVSync(bool enabled) = 0;
		// 获取当前VSync状态
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow()const = 0;
		// 静态工厂方法，根据平台创建窗口实例
		static Window* Create(const WindowProps& props= WindowProps());
	};
}