// 头文件保护宏，防止头文件被重复包含
#pragma once

// 包含事件基类头文件，所有事件都继承自Event
#include "Event.h"
// 包含引擎核心头文件，定义了X_API导出宏等基础设施
#include "XEngine/Core.h"
// 包含Windows.h，可能用于处理Windows特定的事件或功能
#include "Windows.h"

// X引擎命名空间，避免命名冲突
namespace XEngine {

    // 窗口大小改变事件类
    class X_API WindowResizeEvent : public Event
    {
    public:
        // 构造函数：传入改变后的窗口宽度和高度
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {
        }

        // 获取窗口宽度
        inline unsigned int GetWidth() const { return m_Width; }
        // 获取窗口高度
        inline unsigned int GetHeight() const { return m_Height; }

        // 重写基类方法：将事件信息转为字符串，用于调试/日志输出
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        // 宏定义：设置事件类型为WindowResize
        EVENT_CLASS_TYPE(WindowResize)
            // 宏定义：设置事件分类为应用程序事件
            EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        // 存储窗口的宽度和高度
        unsigned int m_Width, m_Height;
    };

    // 窗口关闭事件类
    class X_API WindowCloseEvent : public Event
    {
    public:
        // 构造函数：无参数
        WindowCloseEvent() {}

        // 宏定义：设置事件类型为WindowClose
        EVENT_CLASS_TYPE(WindowClose)
            // 宏定义：设置事件分类为应用程序事件
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    // 应用程序时钟滴答事件（引擎主循环每帧触发）
    class X_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    // 应用程序逻辑更新事件（每帧执行游戏逻辑）
    class X_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    // 应用程序渲染事件（每帧执行画面绘制）
    class X_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}