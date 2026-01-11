add_library(ui)

file(
  GLOB_RECURSE UI_SOURCES Ui/*.c
)

target_sources(ui PUBLIC ${UI_SOURCES})

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ui compiler_flags raylib)
