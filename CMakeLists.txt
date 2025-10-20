cmake_minimum_required(VERSION 4.0)
project(HanoiTower C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(HanoiTower main.c
        tools.c
        tools.h
        solve.c
        solve.h
        render.c
        render.h
        audio.c
        audio.h
        config.c
        config.h
)

target_link_libraries(HanoiTower m)
target_link_libraries(HanoiTower ${SDL2_LIBRARIES})

target_include_directories(HanoiTower PRIVATE ${SDL2_INCLUDE_DIRS})