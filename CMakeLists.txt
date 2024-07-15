cmake_minimum_required(VERSION 3.28.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Chitra VERSION 1.0)
file(GLOB_RECURSE SRC_FILES src/example.c)
add_executable(buld ${SRC_FILES})
# target_include_directories(buld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)