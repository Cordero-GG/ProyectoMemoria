# Incluir headers
include_directories(include)

# Crear ejecutable de la calculadora
add_executable(calculadora src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp
        include/Calculadora.h
        include/Potencia.h)

# Archivos fuente
set(SOURCES
        src/main.cpp
        src/Calculadora.cpp
        src/Potencia.cpp
)

# Decirle que use la librería profiler_lib
target_link_libraries(calculadora PRIVATE profiler_lib)
