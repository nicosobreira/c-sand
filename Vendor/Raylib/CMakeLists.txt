set(RAYLIB_VERSION 5.5)

find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

  message("\t\tBe sure that raylib dependencies are installed!")
  set(FETCHCONTENT_QUIET FALSE)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG ${RAYLIB_VERSION}
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(raylib)
endif()
