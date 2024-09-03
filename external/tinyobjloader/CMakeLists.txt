cmake_minimum_required(VERSION 3.5)
project(tinyobjloader)

add_library(tinyobjloader include/tiny_obj_loader.h tiny_obj_loader.cpp)
target_include_directories(tinyobjloader PUBLIC include/)
