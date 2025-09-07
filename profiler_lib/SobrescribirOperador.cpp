#define DISABLE_PROFILER_MACRO //Evita que el macro de profiler.h afecte este archivo
#include "profiler.h"
#include <new>
#include <cstdlib>
#include <iostream>

// Definición de las sobrecargas del operador new/delete
void* operator new(std::size_t size, const char* file, int line) {
    void* ptr = std::malloc(size);
    if (!ptr) {
        throw std::bad_alloc();
    }
    Profiler::TomarInformacion(ptr, size, file, line);
    return ptr;
}

void* operator new[](std::size_t size, const char* file, int line) {
    return operator new(size, file, line); // Reutiliza la lógica del new simple
}

void operator delete(void* ptr, const char* file, int line) noexcept {
    std::free(ptr);
}

void operator delete[](void* ptr, const char* file, int line) noexcept {
    operator delete(ptr, file, line);
}

// --- Sobrecargas originales ---

void* operator new(std::size_t size) {
    // Llama a la versión con file/line, pero con "unknown" como lugar
    return operator new(size, "unknown", 0);
}

void* operator new[](std::size_t size) {
    return operator new(size); // Reutiliza la lógica del new simple
}

void operator delete(void* ptr) noexcept {
    if (ptr) {
        Profiler::EliminarInformacion(ptr);
    }
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept {
    operator delete(ptr);
}
