cmake_minimum_required(VERSION 3.7)
project(Play)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}) #added

find_package(SDL2 REQUIRED) #added
include_directories(${SDL2_INCLUDE_DIR}) #added

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Player.cpp)
add_executable(Play ${SOURCE_FILES})


target_link_libraries(Play ${SDL2_LIBRARY}) #added