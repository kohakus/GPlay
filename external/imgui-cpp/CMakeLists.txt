cmake_minimum_required(VERSION 3.15)
project(imgui)

set(IMGUI_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../imgui)

set(IMGUI_SRC
    ${IMGUI_ROOT_DIR}/imgui.cpp
    ${IMGUI_ROOT_DIR}/imgui.h
    ${IMGUI_ROOT_DIR}/imstb_rectpack.h
    ${IMGUI_ROOT_DIR}/imstb_textedit.h
    ${IMGUI_ROOT_DIR}/imstb_truetype.h
    ${IMGUI_ROOT_DIR}/imgui_demo.cpp
    ${IMGUI_ROOT_DIR}/imgui_draw.cpp
    ${IMGUI_ROOT_DIR}/imgui_internal.h
    ${IMGUI_ROOT_DIR}/imgui_tables.cpp
    ${IMGUI_ROOT_DIR}/imgui_widgets.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${IMGUI_ROOT_DIR}>
    $<INSTALL_INTERFACE:include>)

foreach(BACKEND glfw opengl3)
	set(NAME imgui_impl_${BACKEND})
	set(HEADER ${IMGUI_ROOT_DIR}/backends/${NAME}.h)
	add_library(${NAME} STATIC ${IMGUI_ROOT_DIR}/backends/${NAME}.cpp ${HEADER})
	target_link_libraries(${NAME} PUBLIC imgui)
	target_include_directories(${NAME} PUBLIC
	    $<BUILD_INTERFACE:${IMGUI_ROOT_DIR}/backends>
	    $<INSTALL_INTERFACE:include>)
endforeach()

target_link_libraries(imgui_impl_glfw PRIVATE glfw)
target_sources(imgui_impl_opengl3 PRIVATE ${IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3_loader.h)
target_link_libraries(imgui_impl_opengl3 PRIVATE OpenGL::GL)
