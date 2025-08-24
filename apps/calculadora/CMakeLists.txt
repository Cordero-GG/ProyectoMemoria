cmake_minimum_required(VERSION 3.10)
project(calculadora)

# Incluir headers
include_directories(include)

# Crear ejecutable de la calculadora
add_executable(calculadora src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp
)
