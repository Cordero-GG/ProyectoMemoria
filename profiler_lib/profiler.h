#ifndef PROYECTOMEMORIA_PROFILER_H
#define PROYECTOMEMORIA_PROFILER_H
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <cstddef>
#include <string>
#include <utility>



struct InfoMemoria
{
    std::size_t size;
    std::chrono::system_clock::time_point timestamp;
    const char* file;
    int line;
};

class  Profiler
{
private:
    static std::unordered_map<void*, InfoMemoria> Metadatos;
    static std::mutex mutexMetadatos;
    static size_t memoriaTotal;
    static size_t cantidadGuardados;
    static size_t maxMemoriaUsada;
    static size_t totalAsignaciones;

public:
    // Métodos de tracking
    static void TomarInformacion(void* ptr, size_t size, const char* file, int line);
    static void EliminarInformacion(void* ptr);
    static std::size_t tomarMemoriaTotal();
    static std::size_t tomarCantidadGuardados();
    static std::size_t tomarMaxMemoriaUsada();
    static std::size_t tomarTotalAsignaciones();
    static void ReportarMemoryLeaks();

    // Nuevo método para obtener resumen por archivo
    static std::unordered_map<std::string, std::pair<size_t, size_t>> obtenerResumenPorArchivo();
};

void* operator new(std::size_t size, const char* file, int line);
void operator delete(void* ptr, const char* file,int line) noexcept;
void* operator new[](std::size_t size, const char* file, int line);
void operator delete[](void* ptr, const char* file, int line) noexcept;

void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
void* operator new[](std::size_t size);
void operator delete[](void* ptr) noexcept;

// Solo definir el macro new en archivos de usuario
#ifndef DISABLE_PROFILER_MACRO
#ifdef USER_SOURCE
#define new new(__FILE__, __LINE__)
#endif
#endif

#endif