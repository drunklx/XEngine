#pragma once

#include "XEngine/Layer.h"
#include "XEngine/Events/MouseEvent.h"
#include "XEngine/Events/KeyEvent.h"
#include "XEngine/Events/ApplicationEvent.h"

namespace XEngine
{
	// ImGui渲染层，负责引擎中Imgui的初始化、渲染、事件拦截与销毁
	class X_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();                     // 构造函数：初始化ImguiLayer成员变量
		virtual ~ImguiLayer() = default;   // 析构函数：默认实现

		void OnAttach() override;          // 层被添加时调用：初始化ImGui上下文、样式、后端
		void OnDetach() override;          // 层被移除时调用：释放ImGui资源
		void OnUpdate() override;          // 每帧更新：渲染ImGui界面
		void OnEvent(Event& event) override; // 事件分发：将所有输入事件传给ImGui处理

	private:
		float m_Time;                     // 记录时间，用于ImGui计算帧间隔

	private:
		// 以下均为事件处理函数：将对应事件转发给ImGui，返回值表示是否被ImGui拦截
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);  // 鼠标按下
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e); // 鼠标松开
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);             // 鼠标滚轮滚动
		bool OnMouseMovedEvent(MouseMovedEvent& e);                   // 鼠标移动
		bool OnKeyPressedEvent(KeyPressedEvent& e);                   // 键盘按键按下
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);                 // 键盘按键松开
		bool OnKeyTypedEvent(KeyTypedEvent& e);                       // 字符输入（如a-z、0-9）
		bool OnWindowResizedEvent(WindowResizeEvent& e);              // 窗口大小改变
	};
}