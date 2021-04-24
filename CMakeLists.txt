cmake_minimum_required(VERSION 3.10.2)
project(Sensor)

set(CMAKE_CXX_STANDARD 14)

### REMOVE IF YOU DO NOT WANT USE FORK() ###
if (NOT UNIX)
    message(FATAL_ERROR "Only Linux distro, we use fork() in this project" )
endif()
SET(CMAKE_CXX_FLAGS "-lboost_thread -pthread -lboost_system")

find_package(Boost REQUIRED COMPONENTS thread system)

add_subdirectory(server)
add_subdirectory(sensor)
