aux_source_directory(. DIR_SRCS)

add_library(FormalModule STATIC ${DIR_SRCS})

target_include_directories(FormalModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})