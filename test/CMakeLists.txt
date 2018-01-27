include_directories(
        ./
        googletest/googletest/include
        googletest/googlemock/include)

add_subdirectory(googletest)

add_sources(. source_files)
add_sources(./common/ source_files)

add_executable(alg_example ${source_files})
target_link_libraries(alg_example gtest gtest_main algs)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
    target_link_libraries(alg_example gcov)
endif ()

add_test(alg_example_test alg_example)
