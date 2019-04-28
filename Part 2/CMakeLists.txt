cmake_minimum_required(VERSION 3.12)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Platform.cpp Platform.h Circle.h Circle.cpp Direction.h)
target_link_libraries(untitled ncurses pthread)