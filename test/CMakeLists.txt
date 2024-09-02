cmake_minimum_required(VERSION 3.15.0)
project(GPlayTests)

add_executable(opengl_window
    opengl_helloworld/window.cpp
)
target_link_libraries(opengl_window ${OPENGL_LIBRARIES}  ${GPLAY_DEPENDENCIES})

add_executable(opengl_triangle
    opengl_helloworld/triangle.cpp
)
target_link_libraries(opengl_triangle ${OPENGL_LIBRARIES}  ${GPLAY_DEPENDENCIES})

add_executable(glm_matrix
    glm_common/matrix.cpp
)
target_link_libraries(glm_matrix ${GPLAY_DEPENDENCIES})
