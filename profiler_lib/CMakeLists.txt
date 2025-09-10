cmake_minimum_required(VERSION 3.10)
project(profiler_lib)

# Biblioteca estática
add_library(profiler_lib STATIC
        profiler.cpp
        SobrescribirOperador.cpp
        socket_client.cpp
        json_serializer.cpp
)

# Incluir directorios
target_include_directories(profiler_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# Habilitar C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Librerías de red para Windows
target_link_libraries(profiler_lib ws2_32)