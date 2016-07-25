cmake_minimum_required(VERSION 3.5)
project(BBTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Starter.cpp)
add_executable(BBtree ${SOURCE_FILES})