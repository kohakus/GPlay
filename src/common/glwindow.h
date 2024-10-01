#ifndef GPLAY_COMMON_GL_WINDOW_H
#define GPLAY_COMMON_GL_WINDOW_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

#include "common/event.h"

namespace gplay {

#define DEFAULT_GPLAY_WINDOW_NAME "GPlay"
#define DEFAULT_GPLAY_WINDOW_HEIGHT (720)
#define DEFAULT_GPLAY_WINDOW_WIDTH (1280)

class GLWindow {
public:
    using CallbackFunc = std::function<void(Event&)>;

    GLWindow();
    GLWindow(const std::string& name);
    GLWindow(const std::string& name, int width, int height);
    ~GLWindow();

    void WindowInit();

    inline bool ShouldClose() const {
        return glfwWindowShouldClose(_window);
    }

public:
    inline std::string GetWindowName() { return _name; }
    inline int GetWindowWidth() { return _width; }
    inline int GetWindowHeight() { return _height; }
    inline GLFWwindow* GetInnerWindow() const { return _window; }

private:
    std::string _name;
    int _width;
    int _height;

    GLFWwindow* _window;
    CallbackFunc _cbfun;
};

} // namespace gplay

#endif // GPLAY_COMMON_GL_WINDOW_H
