file(
  GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS src/*.c
)

add_executable(app ${APP_SOURCES})

target_include_directories(app PRIVATE src)

target_link_libraries(app
  PRIVATE
    project_flags
    raylib
    raygui
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
