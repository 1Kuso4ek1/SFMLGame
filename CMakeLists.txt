cmake_minimum_required(VERSION 3.20)

project(SFMLGame)

set(
    ENGINE_SOURCES

    src/Application.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/Object.cpp
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include/)

add_library(Engine ${ENGINE_SOURCES})
target_link_libraries(Engine SFML::Graphics)

add_executable(SFMLGame main.cpp)
target_link_libraries(SFMLGame Engine)

add_subdirectory(libraries/SFML)
