cmake_minimum_required(VERSION 3.7)

project(project_twodee)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CURRENT_LIST_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(vendor)
add_subdirectory(lib)
add_subdirectory(app)

add_custom_target(write_version_file ALL)

add_custom_command(TARGET write_version_file
        POST_BUILD
        COMMAND ${CMAKE_SOURCE_DIR}/write_version_file.sh "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
        WORKING_DIRECTORY .)

add_custom_target(resource_files ALL ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res)
