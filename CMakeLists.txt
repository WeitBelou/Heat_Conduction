cmake_minimum_required(VERSION 3.2)
project(Heat_Conduction)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
set(CMAKE_AUTOMOC ON)

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("${CMAKE_CURRENT_LIST_DIR}/src")

file(GLOB_RECURSE LIBHEAT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/libheat" *.cpp)
add_library(heat SHARED ${LIBHEAT_SOURCES})
qt5_use_modules(heat Widgets Core)

file(GLOB_RECURSE PLOT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/plot" *.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQCUSTOMPLOT_COMPILE_LIBRARY")
add_library(plot SHARED ${PLOT_SOURCES})
target_link_libraries(plot Qt5::PrintSupport Qt5::Widgets)

file(GLOB GUI_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/gui/*.cpp")
set(LAUNCHER_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"
    ${GUI_SOURCES})

add_executable(launcher ${LAUNCHER_SOURCES})

target_link_libraries(launcher heat)
target_link_libraries(launcher plot)


