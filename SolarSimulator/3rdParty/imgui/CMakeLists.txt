cmake_minimum_required(VERSION 3.00)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


project(imgui)


file(GLOB_RECURSE SOURCES_X CONFIGURE_DEPENDS "./*.cpp")
add_library(imgui STATIC  ${SOURCES_X})

target_include_directories("imgui" PUBLIC ../glfw/include/)

#target_link_libraries(imgui PRIVATE glfw)
