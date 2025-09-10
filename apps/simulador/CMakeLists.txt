cmake_minimum_required(VERSION 3.10)
project(simulador)

# Incluir directorios de headers
include_directories(include)
include_directories(../../profiler_lib)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/chat.cpp
        src/contactos.cpp
)

# Crear el ejecutable
add_executable(simulador ${SOURCES})

# Vincular con la biblioteca del profiler
target_link_libraries(simulador profiler_lib)

# Agregar definiciones necesarias
target_compile_definitions(simulador PRIVATE USER_SOURCE)

# Para Windows, enlazar con Winsock
if(WIN32)
    target_link_libraries(simulador ws2_32)
endif()