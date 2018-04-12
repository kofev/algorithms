add_sources(list source_files)
add_sources(list/reverse source_files)
add_sources(list/loop source_files)
add_sources(array/accumulate source_files)

add_library(algs STATIC ${source_files})
