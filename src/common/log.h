#ifndef GPLAY_COMMON_LOG_H
#define GPLAY_COMMON_LOG_H

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace gplay {

class Log {
public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetLogger() {
        static std::shared_ptr<spdlog::logger> _logger;
        return _logger;
    }

    Log() = delete;
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    ~Log() = delete;
};

#ifdef GPLAY_ENABLE_LOGGING
#define GPLAY_INFO(...) ::gplay::Log::GetLogger()->info(__VA_ARGS__)
#define GPLAY_WARN(...) ::gplay::Log::GetLogger()->warn(__VA_ARGS__)
#define GPLAY_ERROR(...) ::gplay::Log::GetLogger()->error(__VA_ARGS__)
#else
#define GPLAY_INFO(...)
#define GPLAY_WARN(...)
#define GPLAY_ERROR(...)
#endif

}  // namespace gplay

#endif // GPLAY_COMMON_LOG_H
