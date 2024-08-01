cmake_minimum_required(VERSION 3.22)
project(asteroids)
add_executable(asteroids headers/asteroids_clone.hpp src/main.cpp src/asteroids_clone.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC
raylib)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources
                ${CMAKE_CURRENT_BINARY_DIR}/resources)