add_library(clay)

target_compile_options(clay PRIVATE
  -Wno-conversion
  -Wno-sign-conversion
  -Wno-float-conversion
  -Wno-pedantic
  -Wno-error
)

target_sources(clay
  PUBLIC
    clay_renderer_raylib.c

  PUBLIC
    FILE_SET HEADERS
    FILES
      clay.h
)

target_link_libraries(clay PRIVATE raylib)
