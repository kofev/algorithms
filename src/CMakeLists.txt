include_directories(src)

add_sources(list/reverse source_files)

add_library(algs STATIC ${source_files})
