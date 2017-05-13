cmake_minimum_required(VERSION 3.7)

project(twodee)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CURRENT_LIST_DIR}/cmake")

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(vendor)
