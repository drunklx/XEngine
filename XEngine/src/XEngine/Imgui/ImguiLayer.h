#pragma once

#include "XEngine/Layer.h"

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
	private:
		float m_Time=0;                     // 记录时间，用于ImGui计算帧间隔
	};
}