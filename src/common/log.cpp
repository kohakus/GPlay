#include "log.h"

namespace gplay {

void Log::Init() {
    GetLogger() = spdlog::stdout_color_mt("gplay");
    GetLogger()->set_level(spdlog::level::trace);
    GetLogger()->set_pattern("%^[%T][%n] %v%$");
    GPLAY_INFO("Logger Init Done");
}

}  // namespace gplay
