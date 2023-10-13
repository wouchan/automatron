cmake_minimum_required(VERSION 3.21)

### Project settings
set(PROJECT_NAME automatron)
project(${PROJECT_NAME} LANGUAGES C)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

set(CMAKE_C_STANDARD 23)

### Dependecies
include(FetchContent)
set(FETCHCONTENT_QUIET NO)

# raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 4.5.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# raygui
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui
    GIT_TAG 3.6
)

FetchContent_MakeAvailable(raygui)
add_library(raygui INTERFACE)
target_include_directories(raygui INTERFACE ${raygui_SOURCE_DIR}/src)

### Compile-related options
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -Wall -Wextra -Wpedantic -Wstrict-prototypes)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib raygui)
