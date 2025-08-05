cmake_minimum_required(VERSION 3.00)


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project("stb_image")


add_library(stb_image STATIC "stb_image.cpp")
