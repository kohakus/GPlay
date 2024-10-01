#include "common/glwindow.h"
#include "common/log.h"
#include "common/utils.h"

namespace gplay {

GLWindow::GLWindow()
    : _name(DEFAULT_GPLAY_WINDOW_NAME),
      _width(DEFAULT_GPLAY_WINDOW_WIDTH),
      _height(DEFAULT_GPLAY_WINDOW_HEIGHT) {
    WindowInit();
}

GLWindow::GLWindow(const std::string& name)
    : _name(name),
      _width(DEFAULT_GPLAY_WINDOW_WIDTH),
      _height(DEFAULT_GPLAY_WINDOW_HEIGHT) {
    WindowInit();
}

GLWindow::GLWindow(const std::string& name, int width, int height)
    : _name(name), _width(width), _height(height) {
    WindowInit();
}

GLWindow::~GLWindow() {
    glfwTerminate();
}

void GLWindow::WindowInit() {
    glfwSetErrorCallback([](int error, const char* msg) {
        GPLAY_ERROR("[GLFW Error] [{0}] {1}", error, msg);
    });

    if (!glfwInit()) {
        GPLAY_TERMINATE("GLFW init failed");
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    _window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
    if (_window == nullptr) {
        glfwTerminate();
        GPLAY_TERMINATE("GLFW window create failed");
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        GPLAY_TERMINATE("GLAD init failed");
    }

    glfwSwapInterval(1);
    glfwSetWindowUserPointer(_window, &_cbfun);

    glfwSetFramebufferSizeCallback(_window,
        [](GLFWwindow* window, int width, int height) {
            CallbackFunc* fn = static_cast<CallbackFunc*>(glfwGetWindowUserPointer(window));
            if (fn == nullptr) {
                GPLAY_ERROR("FramebufferSizeCallback: No Event Callback function is set");
            } else {
                WindowResizeEvent event(width, height);
                (*fn)(event);
            }
        }
    );

    glfwSetKeyCallback(_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            CallbackFunc* fn = static_cast<CallbackFunc*>(glfwGetWindowUserPointer(window));
            if (!fn) {
                GPLAY_ERROR("KeyCallback: No Event Callback function is set");
            } else {
                switch (action) {
                    case GLFW_PRESS: {
                        KeyEvent event(EventType::kKeyPress, key);
                        (*fn)(event);
                        break;
                    }
                    case GLFW_RELEASE: {
                        KeyEvent event(EventType::kKeyRelease, key);
                        (*fn)(event);
                        break;
                    }
                    case GLFW_REPEAT: {
                        KeyEvent event(EventType::kKeyRepeat, key);
                        (*fn)(event);
                        break;
                    }
                }
            }
        }
    );

    glfwSetCursorPosCallback(_window,
        [](GLFWwindow* window, double xpos, double ypos) {
            CallbackFunc* fn = static_cast<CallbackFunc*>(glfwGetWindowUserPointer(window));
            if (!fn) {
                GPLAY_ERROR("CursorPosCallback: No Event Callback function is set");
            } else {
                MousePositionEvent event(xpos, ypos);
                (*fn)(event);
            }
        }
    );

    glfwSetMouseButtonCallback(_window,
        [](GLFWwindow* window, int button, int action, int mods) {
            CallbackFunc* fn = static_cast<CallbackFunc*>(glfwGetWindowUserPointer(window));
            if (!fn) {
                GPLAY_ERROR("MouseButtonCallback: No Event Callback function is set");
            } else {
                switch (action) {
                    case GLFW_PRESS: {
                        MouseButtonEvent event(EventType::kMousePress, button);
                        (*fn)(event);
                        break;
                    }
                    case GLFW_RELEASE: {
                        MouseButtonEvent event(EventType::kMouseRelease, button);
                        (*fn)(event);
                        break;
                    }
                }
            }
        }
    );

    glfwSetScrollCallback(_window,
        [](GLFWwindow* window, double xOffset, double yOffset) {
            CallbackFunc* fn = static_cast<CallbackFunc*>(glfwGetWindowUserPointer(window));
            if (!fn) {
                GPLAY_ERROR("ScrollCallback: No Event Callback function is set");
            } else {
                MouseScrollEvent event(xOffset, yOffset);
                (*fn)(event);
            }
        }
    );

    GPLAY_INFO("GLWindow Initialised Succ.");
}

} // namespace gplay
