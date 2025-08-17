# Crear ejecutable de la calculadora
add_executable(calculadora main.cpp)

# Decirle que use la librería profiler_lib
target_link_libraries(calculadora PRIVATE profiler_lib)
