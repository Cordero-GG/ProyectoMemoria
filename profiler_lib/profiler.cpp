#include "profiler.h"
#include <iostream>
using namespace std;

//Inicializar las variables estáticas
std::unordered_map<void*, InfoMemoria>Profiler::Metadatos;
std::mutex Profiler::mutexMetadatos;
size_t Profiler::memoriaTotal = 0;
size_t Profiler::cantidadGuardados = 0;

//Implementación de TomarInformacion
void Profiler::TomarInformacion(void* ptr, size_t size, const char* file, int line) {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    InfoMemoria info;
    info.size = size;
    info.timestamp = std::chrono::system_clock::now();
    info.file = file;
    info.line = line;
    Metadatos[ptr] = info;
    memoriaTotal += size;
    cantidadGuardados++;
}

//Implementación de EliminarInformacion
void Profiler::EliminarInformacion(void* ptr) {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    auto it = Metadatos.find(ptr);
    if (it != Metadatos.end()) {
        memoriaTotal -= it->second.size;
        Metadatos.erase(it);
        cantidadGuardados--;
    }
}

//Implementación de tomarMemoriaTotal
std::size_t Profiler::tomarMemoriaTotal()
{
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return memoriaTotal;
}

//Implementación de tomarCantidadGuardados
std::size_t Profiler::tomarCantidadGuardados()
{
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    return cantidadGuardados;
}

//Implementación de ReportarMemoryLeaks
void Profiler::ReportarMemoryLeaks() {
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    if (Metadatos.empty()) {
        std::cout << "No hay memory leaks" << std::endl;
    } else {
        std::cout <<Metadatos.size() << "MEMORY LEAKS DETECTADOS:" << std::endl;
        for (const auto& [direccion, info] : Metadatos) {
            // Calcular cuánto tiempo pasó desde la asignación
            auto ahora = std::chrono::system_clock::now();
            auto duracion = std::chrono::duration_cast<std::chrono::seconds> (ahora - info.timestamp);
            std::cout <<direccion << " - " << info.size
                      << " bytes (hace " << duracion.count() << " segundos) en "
            << info.file << ":" << info.line << std::endl;
        }

        std::cout << "Total de memoria fugada: " << memoriaTotal << " bytes" << std::endl;
    }
}
