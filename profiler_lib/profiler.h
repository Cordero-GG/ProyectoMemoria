#ifndef PROYECTOMEMORIA_PROFILER_H
#define PROYECTOMEMORIA_PROFILER_H
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <cstddef>

struct InfoMemoria
{
    std::size_t size;
    std::chrono::system_clock::time_point timestamp;
    const char* file;
    int line;
};

class Profiler
{
private:
    static std::unordered_map<void*, InfoMemoria> Metadatos; // Mapa para almacenar metadatos de memoria
    static std::mutex mutexMetadatos; // Esto es para que no se ejecuten varios hilos a la vez
    static size_t memoriaTotal;
    static size_t cantidadGuardados;

public:
    // Métodos de tracking
    static void TomarInformacion(void* ptr, size_t size, const char* file, int line);
    static void EliminarInformacion(void* ptr);
    static std::size_t tomarMemoriaTotal(); // Devuelve la memoria total en bytes sirve como un getter
    static std::size_t tomarCantidadGuardados();
    static void ReportarMemoryLeaks(); // Devuelve la cantidad de asignaciones de memoria sirve como un getter
};

void* operator new(std::size_t size, const char* file, int line);
void operator delete(void* ptr, const char* file,int line) noexcept;
void* operator new[](std::size_t size, const char* file, int line);
void operator delete[](void* ptr, const char* file, int line) noexcept;

void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
void* operator new[](std::size_t size);
void operator delete[](void* ptr) noexcept;


#ifndef DISABLE_PROFILER_MACRO
#define new new(__FILE__, __LINE__)
#endif
#endif
