#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Engine
{
	class ENGINE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger()
		{
			return  s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& getClientLogger()
		{
			return  s_ClientLogger;
		}

	private:
		static  std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


}

// Core log macros
#define E_CORE_TRACE(...)	::Engine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define E_CORE_INFO(...)	::Engine::Log::getCoreLogger()->info(__VA_ARGS__)
#define E_CORE_WARN(...)	::Engine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define E_CORE_ERROR(...)	::Engine::Log::getCoreLogger()->error(__VA_ARGS__)
#define E_CORE_CRITICAL(...)	::Engine::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define E_TRACE(...)		::Engine::Log::getClientLogger()->trace(__VA_ARGS__)
#define E_INFO(...)			::Engine::Log::getClientLogger()->info(__VA_ARGS__)
#define E_WARN(...)			::Engine::Log::getClientLogger()->warn(__VA_ARGS__)
#define E_ERROR(...)		::Engine::Log::getClientLogger()->error(__VA_ARGS__)
#define E_CRITICAL(...)		::Engine::Log::getClientLogger()->critical(__VA_ARGS__)