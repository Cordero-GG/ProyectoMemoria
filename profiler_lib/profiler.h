#ifndef PROYECTOMEMORIA_PROFILER_H
#define PROYECTOMEMORIA_PROFILER_H
#include <chrono>
#include <mutex>
#include <unordered_map>// Para malloc y free
#include <cstddef>

struct InfoMemoria
{
    std::size_t size;
    std::chrono::system_clock::time_point timestamp;
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
    static void TomarInformacion(void* ptr, size_t size);
    static void EliminarInformacion(void* ptr);
    static std::size_t tomarMemoriaTotal();// Devuelve la memoria total en bytes sirve como un getter
    static std::size_t tomarCantidadGuardados();
    static void ReportarMemoryLeaks();// Devuelve la cantidad de asignaciones de memoria sirve como un getter
};

void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
void* operator new[](std::size_t size);
void operator delete[](void* ptr) noexcept;

//Iniciar variables estáticas
std::unordered_map<void*, InfoMemoria> Profiler::Metadatos;
std::mutex Profiler::mutexMetadatos;
size_t Profiler::memoriaTotal = 0;
size_t Profiler::cantidadGuardados = 0;

#endif
