cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(../includes/)
include_directories(BEFORE ${QTDIR}/include)

if(APPLE)
  add_definitions(-Wall -O2 -std=c++11 ${Qt5Widgets_DEFINITIONS} -iframework ${QTDIR}/lib -fPIC -stdlib=libc++)
  set(Boost_INCLUDE_DIR /usr/local/Cellar/boost160/1.60.0/include)
  set(Boost_LIBRARY_DIR /usr/local/Cellar/boost160/1.60.0/lib)
elseif(UNIX)
  add_definitions(-Wall -O2 -std=c++11 ${Qt5Widgets_DEFINITIONS} ${QTDIR}/lib -fPIC -lstdc++)
endif()

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_subdirectory(image)
add_subdirectory(utils)
#add_subdirectory(gui)

add_executable(${PROJECT_NAME} ip.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES} Qt5::Widgets Image Utils)#IPGUI) #Utils IPGUI)
