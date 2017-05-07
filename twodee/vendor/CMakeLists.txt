project(vendor)

add_subdirectory(glm)

#set(ENV{GLM_ROOT_DIR} ${PROJECT_SOURCE_DIR}/glm/cmake)

find_package(glm REQUIRED)