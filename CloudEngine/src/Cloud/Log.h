#pragma once

#include "Core.h"
#include "spdlog/spdlog.h" 
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Cloud {
	class  Log {
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {
			return coreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() {
			return clientLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

//REMEMBER STRIPPING THESE MACROS ON DIST BUILD
#define CLD_CORE_ERROR(...) ::Cloud::Log::getCoreLogger()->error(__VA_ARGS__)
#define CLD_CORE_WARN(...)  ::Cloud::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CLD_CORE_INFO(...)  ::Cloud::Log::getCoreLogger()->info(__VA_ARGS__)
#define CLD_CORE_TRACE(...) ::Cloud::Log::getCoreLogger()->trace(__VA_ARGS__)

#define CLD_ERROR(...)		::Cloud::Log::getClientLogger()->error(__VA_ARGS__)
#define CLD_WARN(...)		::Cloud::Log::getClientLogger()->warn(__VA_ARGS__)
#define CLD_INFO(...)		::Cloud::Log::getClientLogger()->info(__VA_ARGS__)
#define CLD_TRACE(...)		::Cloud::Log::getClientLogger()->trace(__VA_ARGS__)