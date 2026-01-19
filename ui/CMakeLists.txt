aux_source_directory(. DIR_SRCS)

add_library(UiModule STATIC ${DIR_SRCS})

target_include_directories(UiModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})