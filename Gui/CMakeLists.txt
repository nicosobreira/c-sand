add_library(gui)

file(
  GLOB_RECURSE GUI_SOURCES Gui/*.c
)

target_sources(gui PUBLIC ${GUI_SOURCES})

target_include_directories(gui PUBLIC .)

target_link_libraries(gui project_flags raylib)
