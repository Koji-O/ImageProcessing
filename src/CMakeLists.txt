cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_definitions(-Wall -O3 -std=c++11)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(../includes/)

add_subdirectory(image)
add_subdirectory(utils)
add_subdirectory(gui)

add_executable(ip.exe main.cpp)

target_link_libraries(ip.exe ${OpenCV_LIBS} Image Utils GUI)
