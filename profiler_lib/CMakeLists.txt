cmake_minimum_required(VERSION 3.10)
project(profiler_lib)

add_library(profiler_lib STATIC profiler.cpp)

# Incluir directorios de encabezados
 target_include_directories(profiler_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
