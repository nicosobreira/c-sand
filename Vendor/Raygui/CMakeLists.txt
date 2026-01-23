add_library(raygui src/raygui.c)

target_compile_options(raygui PRIVATE -Wno-unused-result)

target_include_directories(raygui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(raygui PUBLIC raylib)

