cmake_minimum_required(VERSION 3.0)

project(teslarc)

if(NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE "Release"
        CACHE STRING "Build configuration 'Release' or 'Debug'."
        FORCE
    )
endif()

add_subdirectory("third-party")
add_subdirectory("src")
