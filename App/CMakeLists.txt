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

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(app "-framework IOKit")
    target_link_libraries(app "-framework Cocoa")
    target_link_libraries(app "-framework OpenGL")
endif()

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
