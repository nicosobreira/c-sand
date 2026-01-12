cmake_minimum_required(VERSION 3.15)

project(sand
  LANGUAGES C
)

# Compiler flags and properties
add_library(project_flags INTERFACE)

add_subdirectory(Vendor/Raylib)

add_subdirectory(Vendor/Clay)

add_subdirectory(App)

set(DEBUG_FLAGS
  -g
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
  target_compile_options(project_flags INTERFACE /W4)
else()
  target_compile_options(project_flags INTERFACE
	$<$<CONFIG:Debug>:${DEBUG_FLAGS}>
	$<$<CONFIG:Release>:${RELEASE_FLAGS}>
    $<$<CONFIG:RelWithDebInfo>:${RELWITHDEBINFO_FLAGS}>
  )
endif()

target_compile_features(project_flags INTERFACE c_std_11)

