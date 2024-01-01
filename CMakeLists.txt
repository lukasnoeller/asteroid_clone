cmake_minimum_required(VERSION 3.22)
project(asteroids)
add_executable(asteroids headers/asteroids_clone.hpp src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC
raylib
)

