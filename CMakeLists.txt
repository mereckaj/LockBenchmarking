cmake_minimum_required(VERSION 3.3)
project(ArchLab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp locks.cpp main.cpp Headers/helper.h Headers/stdafx.h helper.cpp BakeryLock.cpp Headers/BakeryLock.hpp TestAndSetLock.cpp Headers/TestAndSetLock.hpp TestAndTestAndSetLock.cpp Headers/TestAndTestAndSetLock.hpp MCS.cpp Headers/MCS.hpp)
add_executable(ArchLab2 ${SOURCE_FILES})