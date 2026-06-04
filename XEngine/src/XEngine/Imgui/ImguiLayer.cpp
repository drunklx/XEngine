#include "xepch.h"
#include "ImguiLayer.h"
#include "imgui.h"
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





}