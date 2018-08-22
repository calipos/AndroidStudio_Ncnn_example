
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../../ncnn/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_library(ncnnshell STATIC src/ncnnshell.cpp)


set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../libs)
set_target_properties(ncnnshell
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY
                      "${distribution_DIR}/ncnnshell/${ANDROID_ABI}")