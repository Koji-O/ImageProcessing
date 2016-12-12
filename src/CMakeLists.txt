cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_definitions(-Wall -O2 -std=c++11 ${Qt5Widgets_DEFINITIONS} -iframework ${QTDIR}/lib -fPIC)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})


include_directories(../includes/)

add_subdirectory(image)
add_subdirectory(utils)
add_subdirectory(gui)

add_executable(ip.exe ip.cpp)

target_link_libraries(ip.exe ${OpenCV_LIBS} Image Utils IPGUI Qt5::Widgets)
