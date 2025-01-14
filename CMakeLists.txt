cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(graphicRenderEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 设置指定的C++版本
# modify flat to -std=c++17 rather than -std=gnu++17
set(CMAKE_CXX_EXTENSIONS OFF)

# box2d
add_subdirectory(3rdparty/box2d)
# lua
add_subdirectory(3rdparty/lua)
# sol2
add_subdirectory(3rdparty/sol2)
# render engine
add_subdirectory(ceres)

include_directories(
        ${PROJECT_SOURCE_DIR}/test
        ${CMAKE_CURRENT_LIST_DIR}/3rdparty)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS test/*.cpp)

# resources copy
file(COPY ./test/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ceres/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_executable(graphicRenderEngine ${SOURCES})
# 链接库
target_link_libraries(graphicRenderEngine ceres box2d liblua sol2)
