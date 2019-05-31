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

#ifdef CLD_ENABLE_ASSERTS
#define CLD_ASSERT(val, ...) { 
		if (!(val)) {
			CLD_ERROR("Failed to Assert: {0}", __VA_ARGS__);
			__debugbreak();
		}
	}
#define CLD_CORE_ASSERT(val, ...) {
		if (!(val)) {
			CLD_CORE_ERROR("Failed to Assert: {0}", __VA_ARGS__);
			__debugbreak();
		}
	}
}
#else 
	#define CLD_ASSERT(val, ...)
	#define CLD_CORE_ASSERT(val, ...)
#endif