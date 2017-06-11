cmake_minimum_required(VERSION 3.7)

project(twodee)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CURRENT_LIST_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(vendor)
add_subdirectory(lib)
add_subdirectory(app)
