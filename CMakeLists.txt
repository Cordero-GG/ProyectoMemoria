cmake_minimum_required(VERSION 3.20)
project(ProyectoMemoria LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crear directorio include si no existe
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann)

# Descargar nlohmann/json.hpp si no existe
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json.hpp)
    file(DOWNLOAD https://github.com/nlohmann/json/releases/download/v3.11.7/json.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann/json.hpp
            TLS_VERIFY ON
    )
endif()

# Subproyectos
add_subdirectory(profiler_lib)
add_subdirectory(tests)
add_subdirectory(apps/calculadora)
add_subdirectory(apps/simulador)
add_subdirectory(interfaz)