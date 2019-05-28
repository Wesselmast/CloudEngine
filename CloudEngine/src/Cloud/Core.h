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
