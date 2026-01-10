cmake_minimum_required(VERSION 3.15)

project(sand
  LANGUAGES C
)

find_package(raylib 5.5 REQUIRED)

# Compiler flags and properties
add_library(compiler_flags INTERFACE)

add_executable(app)

file(
  GLOB_RECURSE APP_SOURCES src/*.c
)

target_sources(app PRIVATE ${APP_SOURCES})

target_include_directories(app PRIVATE src)

target_link_libraries(app compiler_flags raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

set(DEBUG_FLAGS
  -g
  -pedantic
  -Wpedantic
  -Wshadow
  -Wconversion
  -Wformat=2
  -Werror
  -DDEBUG
)

set(RELEASE_FLAGS
  -O3
  -DNDEBUG
)

set(RELWITHDEFINFO_FLAGS
  -O3
  -g
  -fno-omit-frame-pointer
  -DDEBUG
)

if (MSVC)
  target_compile_options(compiler_flags INTERFACE /W4)
else()
  target_compile_options(compiler_flags INTERFACE
	-Wall
	-Wextra
	$<$<CONFIG:Debug>:${DEBUG_FLAGS}>
	$<$<CONFIG:Release>:${RELEASE_FLAGS}>
    $<$<CONFIG:RelWithDebInfo>:${RELWITHDEBINFO_FLAGS}>
  )
endif()

set_target_properties(compiler_flags PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
)

