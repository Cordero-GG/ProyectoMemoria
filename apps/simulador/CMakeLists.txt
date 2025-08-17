# Crear ejecutable del simulador
add_executable(simulador main.cpp)

# Decirle que use la librería profiler_lib
target_link_libraries(simulador PRIVATE profiler_lib)
