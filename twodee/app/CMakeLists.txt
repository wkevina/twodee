project(app LANGUAGES CXX)

set(SOURCE_FILES main.cpp)

add_executable(demo ${SOURCE_FILES})

target_link_libraries(demo twodee)
target_include_directories(demo PUBLIC
        $<TARGET_PROPERTY:twodee,INTERFACE_INCLUDE_DIRECTORIES>)
