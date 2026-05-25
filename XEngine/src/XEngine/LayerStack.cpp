// 包含引擎预编译头（加速编译，包含通用头文件）
#include "xepch.h"

// 包含 LayerStack 类的声明头文件
#include "LayerStack.h"

namespace XEngine
{
	// 【普通层】添加到层栈中
	// 普通层：游戏逻辑、场景等，插入到栈的中间位置（普通层区域）
	void LayerStack::PushLayer(Layer* layer)
	{
		// 在 m_LayerInsert 迭代器位置插入层
		// m_LayerInsert 标记普通层和覆盖层的分界线
		m_Layers.emplace(m_LayerInsert, layer);
	}

	// 【覆盖层/UI层】添加到层栈最后
	// 覆盖层：UI、 ImGui、调试窗口，永远显示在最上层，最后渲染、最先接收事件
	void LayerStack::PushOverlay(Layer* overlay)
	{
		// 直接添加到容器末尾，永远在最上层
		m_Layers.emplace_back(overlay);
	}

	// 从层栈中移除【普通层】
	void LayerStack::PopLayer(Layer* layer)
	{
		// 查找要移除的层
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		// 如果找到了
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);    // 从容器中删除
			m_LayerInsert--;       // 插入指针同步前移
		}
	}

	// 从层栈中移除【覆盖层】
	void LayerStack::PopOverlay(Layer* overlay)
	{
		// 查找覆盖层
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		// 如果找到了就删除
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	// 层栈构造函数
	LayerStack::LayerStack()
	{
		// 初始化插入指针 = 容器开始位置
		// 用于区分：普通层插前面，Overlay 插后面
		m_LayerInsert = m_Layers.begin();
	}

	// 层栈析构函数
	LayerStack::~LayerStack()
	{
		// 遍历所有层，自动释放内存
		// LayerStack 管理所有层的生命周期，自动删除
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}
}