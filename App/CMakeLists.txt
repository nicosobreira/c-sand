add_executable(app)

file(
  GLOB_RECURSE APP_SOURCES src/*.c
)

target_sources(app PRIVATE ${APP_SOURCES})

target_include_directories(app PRIVATE src)

target_link_libraries(app
    compiler_flags
    raylib
    ui
    m
)

