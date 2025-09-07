cmake_minimum_required(VERSION 3.10)
project(calculadora)

# Incluir headers
include_directories(include)

# Crear ejecutable de la calculadora
add_executable(calculadora src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp
        ../../profiler_lib/profiler.h)

# Vincular la biblioteca profiler_lib
 target_link_libraries(calculadora profiler_lib)

# Incluir directorio de profiler_lib para los headers
 target_include_directories(calculadora PRIVATE ../../profiler_lib)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp
)
