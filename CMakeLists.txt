cmake_minimum_required(VERSION 3.2.2)
PROJECT(RTOSSim)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

ADD_EXECUTABLE(RTOSSim ${SOURCES})