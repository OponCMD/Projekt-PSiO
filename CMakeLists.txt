cmake_minimum_required(VERSION 3.16)
project(Help LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include(FetchContent)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)
add_compile_definitions(SFML_STATIC)

add_executable(Help main.cpp
    Config.h
    GameObject.h
    Player.h
    Player.cpp
    Entities.h
    Entities.cpp
    Game.h
    Game.cpp
    PowerUps.h
    PowerUps.cpp
)

target_link_libraries(Help PRIVATE Qt6::Widgets sfml-graphics sfml-window sfml-system opengl32 winmm gdi32)