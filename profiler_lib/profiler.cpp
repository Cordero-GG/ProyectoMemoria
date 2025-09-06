#include "profiler.h"
#include <iostream>
using namespace std;

//Inicializar las variables estáticas
std::unordered_map<void*, InfoMemoria>Profiler::Metadatos;
std::mutex Profiler::mutexMetadatos;
size_t Profiler::memoriaTotal;
size_t Profiler::cantidadGuardados;

//Implementación de TomarInformacion
void Profiler::TomarInformacion(void* ptr, size_t size)
{
    std::lock_guard<std::mutex>>lock(mutexMetadatos); //Bloquea para que no se hagan hilos a la vez
    Metadatos[ptr] = {
        size, std::chrono::system_clock::now() //Guarda el tamaño y el timestamp actual
    };
    memoriaTotal += size;
    cantidadGuardados++;
}

//Implementación de EliminarInformacion
void Profiler::EliminarInformacion(void* ptr)
{
    std::lock_guard<std::mutex> lock(mutexMetadatos);
    auto it = Metadatos.find(ptr);
    if (it != Metadatos.end())
    {
        memoriaTotal -= it->second.size;
        cantidadGuardados--;
        Metadatos.erase(it);
        std::cout << "Eliminacion registrada" <<ptr << std::endl;
    }
    else
    {
        std::cout << "Intento de liberar memoria no registrada: " << ptr << std::endl;
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
            auto duracion = std::chrono::duration_cast<std::chrono::seconds>(
                ahora - info.timestamp);
            std::cout << "   • " << direccion << " - " << info.size
                      << " bytes (hace " << duracion.count() << " segundos)"
                      << std::endl;
        }

        std::cout << "Total de memoria fugada: " << memoriaTotal << " bytes" << std::endl;
    }
}
