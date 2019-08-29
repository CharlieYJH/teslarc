cmake_minimum_required(VERSION 3.8)

project(teslarc)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE "Release"
        CACHE STRING "Build configuration 'Release' or 'Debug'."
        FORCE
    )
endif()

message("Running build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory("third-party")
add_subdirectory("src")
