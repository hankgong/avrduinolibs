#cmake of the whole project

cmake_minimum_required(VERSION 2.8)

project(avrduinolibs C CXX)


#add the library directory
add_subdirectory(corelibs)

#add test example directory
add_subdirectory(test)

set(${CMAKE_C_COMPILER}	avr-gcc)
set(${CMAKE_CXX_COMPILER} avr-g++)


set(PROJECT_C_FLAGS "-ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS				"-g -Os")
set(CMAKE_C_FLAGS_DEBUG			"-g")
set(CMAKE_C_FLAGS_MINSIZEREL	"-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE		"-Os -DNDEBUG")