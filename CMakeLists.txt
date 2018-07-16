cmake_minimum_required(VERSION 3.2.2)
PROJECT(RTOSSim)

file(GLOB MYSOURCES		"src/*.cpp")

ADD_EXECUTABLE(RTOSSim ${MYSOURCES} )