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


#ifdef X_DEBUG
#define X_ENABLE_ASSERTS
#endif

#ifdef X_ENABLE_ASSERTS
	#define X_ASSERT(x, ...) { if(!(x)) { X_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define X_CORE_ASSERT(x, ...) { if(!(x)) { X_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define X_ASSERT(x, ...)
#define X_CORE_ASSERT(x, ...)
#endif // X_ENABLE_ASSERTS

#define X_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)