aux_source_directory(. DIR_SRCS)

add_library(CoreModule STATIC ${DIR_SRCS})

target_include_directories(CoreModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})