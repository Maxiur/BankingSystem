cmake_minimum_required(VERSION 4.2.0)
project(MiniBank)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra -Wpedantic)
include_directories("./include")
file(GLOB_RECURSE sourceFiles ./src/*.cpp)
list(APPEND sourceFiles ./src/sqlite3.c)

add_executable(${PROJECT_NAME} ${sourceFiles})
