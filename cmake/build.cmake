
if (DEFINED CMAKE_C_COMPILER_ID)
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")
        message(STATUS "Using GNU C, Release C flags are: ${CMAKE_C_FLAGS_RELEASE}")

        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
        message(STATUS "Using GNU C, Debug C flags are: ${CMAKE_C_FLAGS_DEBUG}")

        set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_COVERAGE} -Wall -g -O0 --coverage -fprofile-arcs -ftest-coverage")
        message(STATUS "Using GNU C, Coverage C flags are: ${CMAKE_C_FLAGS_COVERAGE}")
    endif ()
endif ()

if (DEFINED CMAKE_CXX_COMPILER_ID)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -Wall")
        message(STATUS "Using GNU C++, Release CXX flags are: ${CMAKE_CXX_FLAGS_RELEASE}")

        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++17 -Wall")
        message(STATUS "Using GNU C++, Debug CXX flags are: ${CMAKE_CXX_FLAGS_DEBUG}")

        set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -std=c++17 -Wall -g -O0 --coverage -fprofile-arcs -ftest-coverage")
        message(STATUS "Using GNU C++, Coverage CXX flags are: ${CMAKE_CXX_FLAGS_COVERAGE}")
    endif ()
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build")
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message(STATUS "Covarage build")
endif ()
