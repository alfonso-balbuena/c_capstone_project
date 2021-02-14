cmake_minimum_required(VERSION 3.17)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(HelloWorld)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

message(STATUS "${CMAKE_SOURCE_DIR}")
message(STATUS "${CMAKE_MODULE_PATH}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)

add_executable(HelloWorld src/capstone.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(HelloWorld ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})