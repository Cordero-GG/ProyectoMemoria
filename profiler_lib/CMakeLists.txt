cmake_minimum_required(VERSION 3.10)
project(profiler_lib)

# Habilitar C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilar TODOS los archivos fuente en un ejecutable
add_executable(profiler_test
        main.cpp
        profiler.cpp
        SobrescrituraOperadores.cpp
)

# Incluir directorios de encabezados
target_include_directories(profiler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})