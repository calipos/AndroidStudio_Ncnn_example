
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ncnnshell/src/main/cpp/ncnnshell/includes)


add_library(ncnnshell STATIC IMPORTED)
set_target_properties(ncnnshell PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/../ncnnshell/lib/${ANDROID_ABI}/libncnnshell.a)

add_library(ncnn STATIC IMPORTED)
set_target_properties(ncnn PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/../ncnn/libs/${ANDROID_ABI}/libncnn.a)

add_library( native-lib
             SHARED
             src/main/cpp/native-lib.cpp )


find_library( log-lib
              log )

target_link_libraries( native-lib
                       ncnnshell
                       ncnn
                       ${log-lib} )