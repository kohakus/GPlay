cmake_minimum_required(VERSION 3.15.0)
project(GPlayTests)

add_executable(opengl_window
    opengl_helloworld/window.cpp
)
target_link_libraries(opengl_window PRIVATE
    OpenGL::GL glad glfw
)

add_executable(opengl_triangle
    opengl_helloworld/triangle.cpp
)
target_link_libraries(opengl_triangle PRIVATE
    OpenGL::GL glad glfw
)

add_executable(glm_matrix
    glm_common/matrix.cpp
)
target_link_libraries(glm_matrix PRIVATE
    glm::glm
)

add_executable(glm_ppm_demo
    glm_common/ppm.cpp
)
target_link_libraries(glm_ppm_demo PRIVATE
    glm::glm
)

add_executable(imgui_example_glfw_opengl3
    imgui_glfw_opengl3/main.cpp
)
target_link_libraries(imgui_example_glfw_opengl3 PRIVATE
    imgui imgui_impl_glfw imgui_impl_opengl3 glfw
)
