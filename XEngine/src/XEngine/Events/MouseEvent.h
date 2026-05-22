// 防止头文件被重复包含
#pragma once

// 包含事件基类头文件（所有事件都继承自Event）
#include "Event.h"


// 引擎命名空间
namespace XEngine {

    // ==============================================
    // 鼠标移动事件
    // ==============================================
    class X_API MouseMovedEvent : public Event
    {
    public:
        // 构造函数：传入鼠标当前 X、Y 坐标
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {
        }

        // 获取鼠标 X 坐标
        inline float GetX() const { return m_MouseX; }
        // 获取鼠标 Y 坐标
        inline float GetY() const { return m_MouseY; }

        // 宏：设置事件类型 = MouseMoved
        EVENT_CLASS_TYPE(MouseMoved)
            // 宏：设置事件分类 = 鼠标事件 + 输入事件
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

            // 重写：将事件转为字符串，用于日志输出
            std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

    private:
        // 存储鼠标坐标
        float m_MouseX, m_MouseY;
    };

    // ==============================================
    // 鼠标滚轮滚动事件
    // ==============================================
    class X_API MouseScrolledEvent : public Event
    {
    public:
        // 构造函数：传入滚轮水平/垂直偏移量
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {
        }

        // 获取水平滚轮偏移（很少用）
        inline float GetXOffset() const { return m_XOffset; }
        // 获取垂直滚轮偏移（上下滚动）
        inline float GetYOffset() const { return m_YOffset; }

        EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

            // 日志输出
            std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

    private:
        float m_XOffset, m_YOffset;
    };

    // ==============================================
    // 鼠标按键事件基类（按下、释放都继承它）
    // ==============================================
    class X_API MouseButtonEvent : public Event
    {
    public:
        // 获取按键编号（左键0，右键1，中键2）
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        // 受保护构造函数，只能子类调用
        MouseButtonEvent(int button)
            : m_Button(button) {
        }

        // 存储哪个鼠标按键被操作
        int m_Button;
    };

    // ==============================================
    // 鼠标按键按下事件
    // ==============================================
    class X_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {
        }

        // 日志输出
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    // ==============================================
    // 鼠标按键释放事件
    // ==============================================
    class X_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {
        }

        // 日志输出
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}