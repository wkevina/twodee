project(app LANGUAGES CXX)

set(SOURCE_FILES main.cpp)

add_executable(demo ${SOURCE_FILES})

target_link_libraries(demo twodee_renderer)
