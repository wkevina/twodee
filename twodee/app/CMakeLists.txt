project(app LANGUAGES CXX)

set(SOURCE_FILES main.cpp)

add_executable(demo ${SOURCE_FILES})

target_link_libraries(demo twodee_renderer)

add_executable(hello_triangle hello_triangle.cpp)

target_link_libraries(hello_triangle twodee_renderer)
