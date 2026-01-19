aux_source_directory(. DIR_SRCS)

add_library(ApiModule STATIC ${DIR_SRCS})

target_include_directories(ApiModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})