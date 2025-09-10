cmake_minimum_required(VERSION 3.10)
project(mensajeria)

# Incluir directorios de headers
include_directories(include)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/chat.cpp
        src/contactos.cpp
)

# Crear el ejecutable
add_executable(mensajeria src/main.cpp
        src/chat.cpp
        src/contactos.cpp
        include/chat.h
        include/contactos.h)