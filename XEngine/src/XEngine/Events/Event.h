// 防止头文件被重复包含（现代C++通用写法）
#pragma once

// 包含引擎核心头文件（Core.h 定义了 X_API 导出宏、基础宏等）
#include"../Core.h"
#include <spdlog/fmt/ostr.h>  // 必须包含这个头文件

// 引擎命名空间，避免全局命名冲突
namespace XEngine {

	// 事件类型枚举（强类型枚举 class enum，更安全）
	enum class EventType
	{
		None = 0,                       // 无事件
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,  // 窗口相关事件
		AppTick, AppUpdate, AppRender,  // 应用程序生命周期事件
		KeyPressed, KeyReleased, KeyTyped,  // 键盘输入事件
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled    // 鼠标输入事件
	};

	// 事件分类枚举（使用位标记，一个事件可以属于多个分类）
	enum EventCategory
	{
		None = 0,                        // 无分类
		EventCategoryApplication = BIT(0),  // 应用程序类事件
		EventCategoryInput = BIT(1),        // 输入类事件
		EventCategoryKeyboard = BIT(2),     // 键盘类事件
		EventCategoryMouse = BIT(3),        // 鼠标移动类事件
		EventCategoryMouseButton = BIT(4)   // 鼠标按键类事件
	};

	// 事件类型宏：给具体事件类自动生成获取事件类型、名称的静态/虚函数
	// ## 是宏拼接符号，# 是把参数转字符串
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// 事件分类宏：给具体事件类自动生成获取分类标记的虚函数
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// 事件基类（所有具体事件都继承此类）—— 引擎导出类 X_API
	class X_API Event
	{
		friend class EventDispatcher;  // 事件分发器需要访问事件的 m_Handled 标记
	public:
		// 纯虚函数：必须由子类实现，获取事件类型
		virtual EventType GetEventType() const = 0;
		// 纯虚函数：必须由子类实现，获取事件名称（用于调试、日志）
		virtual const char* GetName() const = 0;
		// 纯虚函数：必须由子类实现，获取事件分类标记（位组合）
		virtual int GetCategoryFlags() const = 0;

		// 虚函数：将事件转为字符串（默认返回事件名，子类可重写）
		virtual std::string ToString() const { return GetName(); }

		// 内联函数：判断当前事件是否属于某个分类（位与运算）
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		// 事件是否已被处理（标记为true后，事件不再继续传递）
		bool Handled = false;
	};

	// 事件分发器：负责将事件分发给对应类型的处理函数
	class X_API EventDispatcher
	{
		// 模板别名：定义事件回调函数类型（参数为具体事件T&，返回bool）
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		// 构造函数：绑定要分发的事件
		EventDispatcher(Event& event)
			: m_Event(event) {
		}

		// 模板分发函数：将事件分发给对应类型的处理函数
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// 比较事件类型是否匹配
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// 类型安全转换，调用回调函数，并设置事件处理状态
				m_Event.Handled = func(*(T*)&m_Event);
				return true;  // 分发成功
			}
			return false;     // 类型不匹配，分发失败
		}

	private:
		Event& m_Event;  // 引用：绑定要分发的事件
	};

	
	// 重载 << 运算符：方便事件输出到流（日志、打印调试）
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
// ✅ 核心修复：fmt 适配 ostream 重载
template<>
struct fmt::formatter<XEngine::Event> : fmt::ostream_formatter {};