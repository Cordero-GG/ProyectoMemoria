cmake_minimum_required(VERSION 3.10)
project(calculadora)

# Incluir headers
include_directories(include)
include_directories(../../profiler_lib)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp
)

# Crear ejecutable de la calculadora
add_executable(calculadora ${SOURCES})

# Vincular la biblioteca profiler_lib
target_link_libraries(calculadora profiler_lib)

# Agregar definiciones necesarias
target_compile_definitions(calculadora PRIVATE USER_SOURCE)

# Para Windows, enlazar con Winsock
if(WIN32)
 target_link_libraries(calculadora ws2_32)
endif()