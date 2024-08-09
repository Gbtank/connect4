cmake_minimum_required(VERSION 3.0.0)
project(Connect4 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Connect4 src/direction.cpp src/connection.cpp src/board.cpp src/main.cpp)
target_include_directories(Connect4 PRIVATE ${PROJECT_SOURCE_DIR}/include)