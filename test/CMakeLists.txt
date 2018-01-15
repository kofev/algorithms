add_sources(list/reverse source_files)

add_executable(alg_example ${source_files})
target_link_libraries(alg_example gtest gtest_main algs)

add_test(alg_example_test alg_example)
