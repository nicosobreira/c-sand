add_executable(app)

file(
  GLOB_RECURSE APP_SOURCES src/*.c
)

target_sources(app PRIVATE ${APP_SOURCES})

target_include_directories(app PRIVATE src)

target_link_libraries(app
  PRIVATE
    project_flags
    raylib
    clay
    m
)

# target_compile_options(app PRIVATE
#   -Wall
#   -Wextra
#   -pedantic
#   -Wpedantic
#   -Wshadow
#   -Wconversion
#   -Wformat=2
#   -Werror
# )
