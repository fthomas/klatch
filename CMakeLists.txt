cmake_minimum_required(VERSION 2.6)

project(Klatch)
string(TOLOWER ${CMAKE_PROJECT_NAME} PROJECT_NAME_LOWER)

set(klatch_VERSION_MAJOR "0")
set(klatch_VERSION_MINOR "0")
set(klatch_VERSION "${klatch_VERSION_MAJOR}.${klatch_VERSION_MINOR}")

# Enable more warnings if g++ or clang is used.
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER MATCHES clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

enable_testing()
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_COPY ${CMAKE_COMMAND} -E copy)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
list(REMOVE_ITEM CMAKE_CXX_FLAGS "-ansi")

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(src)
add_subdirectory(tests)
