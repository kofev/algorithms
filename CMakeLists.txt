cmake_minimum_required(VERSION 3.5)
project(algorithms C CXX)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build configuration: ${CMAKE_BUILD_TYPE}")

enable_testing()

function(add_sources src_dir src_list)
    file(GLOB tmp_src ${src_dir}/*.cpp ${src_dir}/*.c ${src_dir}/*.h)
    set(${src_list} ${${src_list}} ${tmp_src} PARENT_SCOPE)
endfunction()

include_directories(
        src
        googletest/googletest/include
        googletest/googlemock/include)

add_subdirectory(googletest)
add_subdirectory(src)
add_subdirectory(test)
