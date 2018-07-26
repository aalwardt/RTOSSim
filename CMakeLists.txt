cmake_minimum_required(VERSION 3.2.2)
PROJECT(RTOSSim)

include_directories(include)
include_directories(include/schedulers)

file(GLOB SOURCES "src/*.cpp" "src/schedulers/*.cpp")

ADD_EXECUTABLE(RTOSSim ${SOURCES})