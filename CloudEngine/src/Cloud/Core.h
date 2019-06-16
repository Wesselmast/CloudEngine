#pragma once

#ifdef CLD_PLATFORM_WINDOWS
	#ifdef CLD_BUILD_DLL
		#define CLOUD_API __declspec(dllexport)
	#else
		#define CLOUD_API __declspec(dllimport)
	#endif
#else 
	#error Cloud Engine only supports Windows!
#endif

#ifdef CLD_DEBUG
	#define CLD_ENABLE_ASSERTS
#endif

#ifdef CLD_ENABLE_ASSERTS
	#define CLD_ASSERT(condition, ...) {  if (!(condition)) { CLD_ERROR("Failed to Assert: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CLD_CORE_ASSERT(condition, ...) { if (!(condition)) { CLD_CORE_ERROR("Failed to Assert: {0}", __VA_ARGS__); __debugbreak(); } }
#else 
	#define CLD_ASSERT(condition, ...)
	#define CLD_CORE_ASSERT(condition, ...)
#endif

#define BIND_EVENT_FUNC(func)std::bind(&func, this, std::placeholders::_1)