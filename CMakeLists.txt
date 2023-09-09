cmake_minimum_required(VERSION 3.26)
project(pong)

set(CMAKE_CXX_STANDARD 20)
set(RAYLIB_VERSION 4.2.0)

find_package(raylib ${RAYLIB_VERSION} REQUIRED)

add_executable(pong main.cpp
        pong.cpp
        pong.hpp)

target_link_libraries(pong raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()