add_library(clay)

target_link_libraries(clay PRIVATE raylib)

target_sources(clay
  PUBLIC
    clay_renderer_raylib.c

  PUBLIC
    FILE_SET HEADERS
    FILES
      clay.h
)

if (NOT MSVC)
  target_compile_options(clay PRIVATE
      -Wno-conversion
      -Wno-sign-conversion
      -Wno-float-conversion
      -Wno-pedantic

      $<$<CONFIG:Debug>:-g>
      $<$<CONFIG:Release>:-O3>
      $<$<CONFIG:RelWithDebInfo>:-g -O3>
  )
endif()
