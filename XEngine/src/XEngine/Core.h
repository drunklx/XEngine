#pragma once

#ifdef X_PLATFORM_WINDOWS
	#ifdef X_BUILD_DLL
#define X_API __declspec(dllexport)
	#else
#define X_API __declspec(dllimport)
	#endif // X_BUILD_DLL
#else 
	#error XEngine only supports Windows!
#endif // X_PLATFORM_WINDOWS
