#include "xepch.h"
#include "ImguiLayer.h"
#include "imgui.h"
// OpenGL 渲染 ImGui 的实现
#include "Platform/OpenGL/ImguiOpenGLRenderer.h"
// 应用程序类，获取窗口信息
#include "XEngine/Application.h"
// GLFW 窗口库
#include "GLFW/glfw3.h"
// OpenGL 函数加载
#include <glad/glad.h>

namespace XEngine
{
	// 构造函数：调用父类Layer，设置层名称
	ImguiLayer::ImguiLayer()
		: Layer("ImguiLayer")
	{
	}

	// 工具函数：把 GLFW 按键码 转换成 ImGui 能识别的按键码
	ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode)
	{
		IM_UNUSED(scancode);
		switch (keycode)
		{
		case GLFW_KEY_TAB: return ImGuiKey_Tab;
		case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
		case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
		case GLFW_KEY_UP: return ImGuiKey_UpArrow;
		case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
		case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
		case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
		case GLFW_KEY_HOME: return ImGuiKey_Home;
		case GLFW_KEY_END: return ImGuiKey_End;
		case GLFW_KEY_INSERT: return ImGuiKey_Insert;
		case GLFW_KEY_DELETE: return ImGuiKey_Delete;
		case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
		case GLFW_KEY_SPACE: return ImGuiKey_Space;
		case GLFW_KEY_ENTER: return ImGuiKey_Enter;
		case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
		case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
		case GLFW_KEY_COMMA: return ImGuiKey_Comma;
		case GLFW_KEY_MINUS: return ImGuiKey_Minus;
		case GLFW_KEY_PERIOD: return ImGuiKey_Period;
		case GLFW_KEY_SLASH: return ImGuiKey_Slash;
		case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
		case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
		case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
		case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
		case GLFW_KEY_WORLD_1: return ImGuiKey_Oem102;
		case GLFW_KEY_WORLD_2: return ImGuiKey_Oem102;
		case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
		case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
		case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
		case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
		case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
		case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
		case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
		case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
		case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
		case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
		case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
		case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
		case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
		case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
		case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
		case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
		case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
		case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
		case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
		case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
		case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
		case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
		case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
		case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
		case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
		case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
		case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
		case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
		case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
		case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
		case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
		case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
		case GLFW_KEY_MENU: return ImGuiKey_Menu;
		case GLFW_KEY_0: return ImGuiKey_0;
		case GLFW_KEY_1: return ImGuiKey_1;
		case GLFW_KEY_2: return ImGuiKey_2;
		case GLFW_KEY_3: return ImGuiKey_3;
		case GLFW_KEY_4: return ImGuiKey_4;
		case GLFW_KEY_5: return ImGuiKey_5;
		case GLFW_KEY_6: return ImGuiKey_6;
		case GLFW_KEY_7: return ImGuiKey_7;
		case GLFW_KEY_8: return ImGuiKey_8;
		case GLFW_KEY_9: return ImGuiKey_9;
		case GLFW_KEY_A: return ImGuiKey_A;
		case GLFW_KEY_B: return ImGuiKey_B;
		case GLFW_KEY_C: return ImGuiKey_C;
		case GLFW_KEY_D: return ImGuiKey_D;
		case GLFW_KEY_E: return ImGuiKey_E;
		case GLFW_KEY_F: return ImGuiKey_F;
		case GLFW_KEY_G: return ImGuiKey_G;
		case GLFW_KEY_H: return ImGuiKey_H;
		case GLFW_KEY_I: return ImGuiKey_I;
		case GLFW_KEY_J: return ImGuiKey_J;
		case GLFW_KEY_K: return ImGuiKey_K;
		case GLFW_KEY_L: return ImGuiKey_L;
		case GLFW_KEY_M: return ImGuiKey_M;
		case GLFW_KEY_N: return ImGuiKey_N;
		case GLFW_KEY_O: return ImGuiKey_O;
		case GLFW_KEY_P: return ImGuiKey_P;
		case GLFW_KEY_Q: return ImGuiKey_Q;
		case GLFW_KEY_R: return ImGuiKey_R;
		case GLFW_KEY_S: return ImGuiKey_S;
		case GLFW_KEY_T: return ImGuiKey_T;
		case GLFW_KEY_U: return ImGuiKey_U;
		case GLFW_KEY_V: return ImGuiKey_V;
		case GLFW_KEY_W: return ImGuiKey_W;
		case GLFW_KEY_X: return ImGuiKey_X;
		case GLFW_KEY_Y: return ImGuiKey_Y;
		case GLFW_KEY_Z: return ImGuiKey_Z;
		case GLFW_KEY_F1: return ImGuiKey_F1;
		case GLFW_KEY_F2: return ImGuiKey_F2;
		case GLFW_KEY_F3: return ImGuiKey_F3;
		case GLFW_KEY_F4: return ImGuiKey_F4;
		case GLFW_KEY_F5: return ImGuiKey_F5;
		case GLFW_KEY_F6: return ImGuiKey_F6;
		case GLFW_KEY_F7: return ImGuiKey_F7;
		case GLFW_KEY_F8: return ImGuiKey_F8;
		case GLFW_KEY_F9: return ImGuiKey_F9;
		case GLFW_KEY_F10: return ImGuiKey_F10;
		case GLFW_KEY_F11: return ImGuiKey_F11;
		case GLFW_KEY_F12: return ImGuiKey_F12;
		case GLFW_KEY_F13: return ImGuiKey_F13;
		case GLFW_KEY_F14: return ImGuiKey_F14;
		case GLFW_KEY_F15: return ImGuiKey_F15;
		case GLFW_KEY_F16: return ImGuiKey_F16;
		case GLFW_KEY_F17: return ImGuiKey_F17;
		case GLFW_KEY_F18: return ImGuiKey_F18;
		case GLFW_KEY_F19: return ImGuiKey_F19;
		case GLFW_KEY_F20: return ImGuiKey_F20;
		case GLFW_KEY_F21: return ImGuiKey_F21;
		case GLFW_KEY_F22: return ImGuiKey_F22;
		case GLFW_KEY_F23: return ImGuiKey_F23;
		case GLFW_KEY_F24: return ImGuiKey_F24;
		default: return ImGuiKey_None;
		}
	}

	// 层被附加时调用：初始化 ImGui 上下文 + OpenGL 后端
	void XEngine::ImguiLayer::OnAttach()
	{
		// 创建 ImGui 主上下文（必须第一步）
		ImGui::CreateContext();

		// 获取 ImGui IO 配置
		ImGuiIO& io = ImGui::GetIO();
		// 启用鼠标样式支持
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		// 启用设置鼠标位置功能
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// 初始化 OpenGL3 渲染器，使用 GLSL #version 410
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	// 层被分离时调用：释放 ImGui 资源（目前空实现）
	void XEngine::ImguiLayer::OnDetach()
	{
	}

	// 每帧更新：渲染 ImGui 界面
	void XEngine::ImguiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		// 获取应用程序实例
		Application& app = Application::Get();
		// 设置 ImGui 显示尺寸 = 窗口大小
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		// 计算帧间隔时间 deltaTime
		float time = (float)ImGui::GetTime();
		io.DeltaTime = m_Time > 0 ? time - m_Time : (1.0f / 60.0f);
		m_Time = time;

		// 开始新一帧 ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// 显示 ImGui 官方演示窗口（调试用）
		static bool show = false;
		ImGui::ShowDemoWindow(&show);

		// 渲染 ImGui 绘制数据
		ImGui::Render();
		// 使用 OpenGL 渲染 ImGui
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	// 事件处理：把引擎事件分发给 ImGui
	void XEngine::ImguiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		// 分发各种输入事件给 ImGui
		dispatcher.Dispatch<MouseButtonPressedEvent>(X_BIND_EVENT_FN(ImguiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(X_BIND_EVENT_FN(ImguiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(X_BIND_EVENT_FN(ImguiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<MouseMovedEvent>(X_BIND_EVENT_FN(ImguiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(X_BIND_EVENT_FN(ImguiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(X_BIND_EVENT_FN(ImguiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(X_BIND_EVENT_FN(ImguiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(X_BIND_EVENT_FN(ImguiLayer::OnWindowResizedEvent));
	}

	// 鼠标按下事件：通知 ImGui 对应按键按下
	bool XEngine::ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	// 鼠标松开事件：通知 ImGui 对应按键松开
	bool XEngine::ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	// 鼠标滚轮事件：通知 ImGui 滚轮偏移量
	bool XEngine::ImguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	// 鼠标移动事件：通知 ImGui 新鼠标位置
	bool XEngine::ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	// 键盘按下事件：转换按键并通知 ImGui
	bool XEngine::ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		// 把 GLFW 按键转为 ImGui 按键
		ImGuiKey keycode = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), e.GetScanCode());
		io.KeysData[keycode - ImGuiKey_NamedKey_BEGIN].Down = true;

		// 更新 Ctrl/Shift/Alt/Win 键状态
		io.KeyCtrl = io.KeysData[ImGuiKey_LeftCtrl - ImGuiKey_NamedKey_BEGIN].Down || io.KeysData[ImGuiKey_RightCtrl - ImGuiKey_NamedKey_BEGIN].Down;
		io.KeyShift = io.KeysData[ImGuiKey_LeftShift - ImGuiKey_NamedKey_BEGIN].Down || io.KeysData[ImGuiKey_RightShift].Down;
		io.KeyAlt = io.KeysData[ImGuiKey_LeftAlt - ImGuiKey_NamedKey_BEGIN].Down || io.KeysData[ImGuiKey_RightAlt].Down;
		io.KeySuper = io.KeysData[ImGuiKey_LeftSuper - ImGuiKey_NamedKey_BEGIN].Down || io.KeysData[ImGuiKey_RightSuper].Down;
		return false;
	}

	// 键盘松开事件：通知 ImGui 按键松开
	bool XEngine::ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey keycode = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), e.GetScanCode());
		io.KeysData[keycode - ImGuiKey_NamedKey_BEGIN].Down = false;
		return false;
	}

	// 字符输入事件：把输入的字符传给 ImGui（如输入框打字）
	bool XEngine::ImguiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned int)keycode);
		return false;
	}

	// 窗口大小改变事件：通知 ImGui 尺寸变化，并重置 OpenGL 视口
	bool XEngine::ImguiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}