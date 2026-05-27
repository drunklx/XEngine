-- 定义一个工作区(解决方案)，名为 XEngine
workspace "XEngine"
	-- 生成64位程序
	architecture "x64"

	-- 三种编译配置
	configurations 	{
		"Debug",	-- 调试模式（带调试信息，性能低）
		"Release",	-- 发布模式（优化，性能高）
		"Dist"		-- 发行模式（极致优化）
	}

	-- 输出目录变量：配置-系统-架构
	-- 例子：Debug-Windows-x64
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir={}
	IncludeDir["GLFW"] = "XEngine/vendor/GLFW/include"
	IncludeDir["Glad"] = "XEngine/vendor/Glad/include"
	IncludeDir["Imgui"]= "XEngine/vendor/Imgui"

	include "XEngine/vendor/GLFW"
	include "XEngine/vendor/Glad"
	include "XEngine/vendor/Imgui"
-- ======================================================
-- 项目1：XEngine 引擎核心库（动态库 DLL）
-- ======================================================
project "XEngine"
location "XEngine"			-- 项目文件放在 XEngine 文件夹
kind "SharedLib"			-- 编译类型：动态链接库（.dll）
language "C++"				-- 使用 C++ 语言

-- 最终生成的 exe/dll 输出目录
targetdir ("bin/"..outputdir.."/%{prj.name}")
-- 编译中间文件目录（.obj 等）
objdir ("bin-int/"..outputdir.."/%{prj.name}")

pchheader "xepch.h"			-- 预编译头文件
pchsource "XEngine/src/xepch.cpp"	-- 预编译头文件的源文件

-- 包含的源文件：所有 .h 和 .cpp 文件
files
{
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp"
}

-- 头文件包含目录（让编译器能找到 spdlog）
includedirs
{
	"%{prj.name}/vendor/spdlog/include",
	"%{prj.name}/src",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.Glad}",
	"%{IncludeDir.Imgui}"
}

links
{
	"Imgui",	-- 链接 Imgui 库（它会在 Imgui 项目里生成）""
	"Glad",	-- 链接 GLAD 库（它会在 GLAD 项目里生成）"
	"GLFW",	-- 链接 GLFW 库（它会在 GLFW 项目里生成）
	"opengl32.lib" -- 链接 Windows 的 OpenGL 库
}

-- ==================== Windows 平台配置 ====================
filter "system:windows"
	cppdialect "C++17"			-- 使用 C++17 标准
	systemversion "latest"		-- 使用最新 Windows SDK
	buildoptions { "/utf-8" }        -- 使用 UTF-8 字符集

	-- 预处理器宏定义
	defines
	{
		"X_PLATFORM_WINDOWS",	-- 标记当前是 Windows 系统
		"X_BUILD_DLL",			-- 标记正在编译 DLL（用于导出符号）
		"GLFW_INCLUDE_NONE"		-- 告诉 GLFW 不要包含 OpenGL 头文件（我们用 GLAD）"
	}

	-- 编译后自动执行：把生成的 DLL 复制到 Sandbox 目录
	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
	}

-- ==================== 不同编译模式配置 ====================
filter "configurations:Debug"
	defines "X_DEBUG"			-- 定义调试宏
	buildoptions "/MDd"
	symbols "On"				-- 生成调试信息

filter "configurations:Release"
	defines "X_RELEASE"			-- 定义发布宏
	buildoptions "/MD"
	optimize "On"				-- 开启优化

filter "configurations:Dist"
	defines "X_DIST"			-- 定义发行宏
	buildoptions "/MD"
	optimize "Full"				-- 全量优化

-- ======================================================
-- 项目2：Sandbox 测试程序（控制台应用）
-- ======================================================
project "Sandbox"
	location "Sandbox"			-- 项目文件放在 Sandbox 文件夹
	kind "ConsoleApp"			-- 编译类型：控制台应用程序（.exe）
	language "C++"				-- 使用 C++ 语言

	-- 输出目录
	targetdir ("bin/"..outputdir.."/%{prj.name}")
	-- 中间文件目录
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	-- 包含自己的源码
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- 链接 XEngine 库（依赖它）
	links
	{
		"XEngine"
	}

	-- 头文件包含目录
	includedirs
	{
		"XEngine/vendor/spdlog/include",	-- 日志库
		"XEngine/src"						-- 引擎头文件
	}

-- ==================== Windows 平台配置 ====================
filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"
	buildoptions { "/utf-8" }

	defines
	{
		"X_PLATFORM_WINDOWS",	-- 标记 Windows 系统
	}

-- ==================== 编译模式配置 ====================
filter "configurations:Debug"
	defines "X_DEBUG"
	buildoptions "/MDd"
	symbols "On"

filter "configurations:Release"
	defines "X_RELEASE"
	buildoptions "/MD"
	optimize "On"

filter "configurations:Dist"
	defines "X_DIST"
	buildoptions "/MDd"
	optimize "Full"