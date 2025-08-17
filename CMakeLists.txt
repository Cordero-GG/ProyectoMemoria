cmake_minimum_required(VERSION 3.20)

# Nombre global del proyecto
project(ProyectoMemoria LANGUAGES CXX)

# Usaremos C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Subproyectos
add_subdirectory(profiler_lib)
add_subdirectory(apps/calculadora)
add_subdirectory(apps/simulador)
add_subdirectory(interfaz)
