project(ip)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_COMPILER /usr/bin/clang++ )
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(OpenCV REQUIRED)
find_package(Qt5Widgets REQUIRED)
add_subdirectory(src)