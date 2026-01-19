aux_source_directory(. DIR_SRCS)

add_library(ToolsModule STATIC ${DIR_SRCS})

target_include_directories(ToolsModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})