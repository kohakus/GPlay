#ifndef GPLAY_COMMON_UTILS_H
#define GPLAY_COMMON_UTILS_H

namespace gplay {

#define GPLAY_TERMINATE(message)                          \
    do {                                                  \
        GPLAY_ERROR("{}", #message, __FILE__, __LINE__);  \
        std::terminate();                                 \
    } while (false)

} // namespace gplay

#endif // GPLAY_COMMON_UTILS_H
