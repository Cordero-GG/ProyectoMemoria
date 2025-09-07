cmake_minimum_required(VERSION 3.10)
project(profiler_tests)

# Ejecutable de prueba
add_executable(profiler_test main.cpp)

# Enlazar con la biblioteca
target_link_libraries(profiler_test profiler_lib)

# Incluir directorios
target_include_directories(profiler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../profiler_lib)