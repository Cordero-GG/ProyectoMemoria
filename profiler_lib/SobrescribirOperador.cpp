#include "profiler.h"
#include <new> // Para std::bad_alloc
#include <cstdlib> // Para std::malloc y std::free

void* operator new(size_t size)
{
    void* ptr = std::malloc(size);
    if (ptr)
    {
        Profiler::TomarInformacion(ptr, size);
    }
    else
        {
        throw std::bad_alloc();
        }
    return ptr;
}

void* operator new[](size_t size)
{
    return operator new(size); //Usa la misma lógica que el new básico
}

void* operator delete(void* ptr) noexcept
{
    if (ptr)
    {
        Profiler::EliminarInformacion(ptr);
    }
    std::free(ptr);
}

void* operator delete[](void* ptr)
{
    return operator delete(ptr);
}