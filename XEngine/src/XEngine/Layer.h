// 防止头文件被重复包含（#pragma once 是现代编译器通用写法，比 #ifndef 更简洁）
#pragma once

// 包含引擎核心头文件（通常包含宏定义、导出符号X_API、基础类型、配置等）
#include "Core.h"

// 包含事件系统头文件，因为本类需要处理事件（OnEvent函数参数用到Event&）
#include "XEngine/Events/Event.h"

// XEngine 命名空间：所有引擎代码都放在这个命名空间内，避免与项目代码命名冲突
namespace XEngine
{
	// X_API 宏：
	// 编译DLL时 = __declspec(dllexport) 导出类
	// 调用DLL时 = __declspec(dllimport) 导入类
	// 作用：让Layer类可以在引擎(DLL)和游戏程序(EXE)之间正常使用
	class X_API Layer
	{
	public:
		// 构造函数
		// 参数：debugName - 层的名称（用于日志、调试、编辑器显示），默认值 "Layer"
		Layer(const std::string& name = "Layer");

		// 虚析构函数
		// 重要：因为Layer是基类，会被继承，必须写虚析构，确保子类析构时能正确调用
		virtual ~Layer();

		// 虚函数：层被附加（添加到引擎）时调用
		// 用途：初始化资源、注册监听、启动逻辑等
		virtual void OnAttach();

		// 虚函数：层被分离（从引擎移除）时调用
		// 用途：释放资源、清理数据、反注册监听等
		virtual void OnDetach();

		// 虚函数：每帧更新时调用
		// 用途：游戏逻辑更新、物理、输入处理、场景逻辑等
		virtual void OnUpdate();

		// 虚函数：ImGui渲染时调用
		// 用途：绘制调试窗口、编辑器UI、游戏内UI等
		virtual void OnImGuiRender();

		// 虚函数：事件回调函数
		// 当引擎产生事件（窗口、鼠标、键盘、触摸等）时，会传递到该层
		// 参数：event - 事件基类引用，所有事件都会通过这里传入
		virtual void OnEvent(Event& event);

		// 内联成员函数：获取层的调试名称
		// const & 保证高效且不修改数据
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		// 层的调试名称（日志、编辑器显示用）
		// protected：子类可以直接访问，外部不能访问
		std::string m_DebugName;
	};
}