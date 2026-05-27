// 头文件保护：防止该头文件被多次包含编译
#pragma once

// 包含事件系统基类头文件（所有事件都继承自这里的Event类）
#include "Event.h"


// X引擎命名空间，避免全局命名冲突
namespace XEngine {

    //=====================================================
    // 键盘事件基类（抽象类）
    // 所有键盘相关事件（按下、释放）都继承自这个类
    //=====================================================
    class X_API KeyEvent : public Event
    {
    public:
        // 内联函数：获取按键编码（比如A键=65，回车=13等）
        inline int GetKeyCode() const { return m_KeyCode; }

        inline int GetScanCode() const { return m_ScanCode; }
        // 使用宏：设置事件分类 = 键盘事件 + 输入事件
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        // 受保护构造函数：只能被子类调用，禁止直接创 建                  KeyEvent对象
        KeyEvent(int keycode,int scancode=0)
            : m_KeyCode(keycode),m_ScanCode(scancode) {
        }

        // 成员变量：存储当前按键的编码
        int m_KeyCode;
        int m_ScanCode;
    };

    //=====================================================
    // 按键按下事件
    //=====================================================
    class X_API KeyPressedEvent : public KeyEvent
    {
    public:
        // 构造函数：参数=按键编码 + 长按重复次数
        KeyPressedEvent(int keycode, int repeatCount,int scanCode=0)
            : KeyEvent(keycode,scanCode), m_RepeatCount(repeatCount) {
        }

        // 获取按键长按重复次数（按住不放会重复触发）
        inline int GetRepeatCount() const { return m_RepeatCount; }
        
        // 重写：将事件转为可读字符串，用于日志输出
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        // 使用宏：设置事件类型为 KeyPressed
        EVENT_CLASS_TYPE(KeyPressed)

    private:
        // 重复次数：长按按键时会持续累加
        int m_RepeatCount;
    };

    //=====================================================
    // 按键释放事件
    //=====================================================
    class X_API KeyReleasedEvent : public KeyEvent
    {
    public:
        // 构造函数：参数=按键编码
        KeyReleasedEvent(int keycode,int scancode=0)
            : KeyEvent(keycode,scancode) {
        }

        // 重写：转为日志字符串
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        // 使用宏：设置事件类型为 KeyReleased
        EVENT_CLASS_TYPE(KeyReleased)
    };

    class X_API KeyTypedEvent : public KeyEvent
    {
    public:
        // 构造函数：参数=按键编码
        KeyTypedEvent(int keycode, int scancode = 0)
            : KeyEvent(keycode, scancode) {
        }

        // 重写：转为日志字符串
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        // 使用宏：设置事件类型为 KeyTyped
        EVENT_CLASS_TYPE(KeyTyped)
    };
}