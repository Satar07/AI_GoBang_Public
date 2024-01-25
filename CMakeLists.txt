# Adapted from https://github.com/SasLuca/raylib-cmake-template/blob/master/CMakeLists.txt
# License: zlib https://github.com/SasLuca/raylib-cmake-template/blob/master/LICENSE
# Changes: adding dependencies, adding raygui, adding source files, adding compiler flags, adding asset path macro
cmake_minimum_required(VERSION 3.0)
project(ai_backgammon)
set(CMAKE_C_STANDARD 99)

# Adding Raylib
# License: zlib https://github.com/raysan5/raylib/blob/master/LICENSE
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Adding Raygui
# License: zlib https://github.com/raysan5/raygui/blob/master/LICENSE
FetchContent_Declare(
        raygui
        GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raygui)

# Declaring our executable
add_executable(${PROJECT_NAME})

# Specify the raygui include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${raygui_SOURCE_DIR}/src)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/sources/Object/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/sources/ChessCore/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/sources/General/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Adding our compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable