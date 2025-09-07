#include "../profiler_lib/profiler.h"
#include <iostream>
#include <thread>
#include <vector>

// Función que causa un leak en otro contexto
void leakEnFuncion() {
    int* leak_int = new int(999); // LEAK intencional aquí
    std::cout << "Leak intencional creado en funcion: " << *leak_int << std::endl;
    // NOTA: No liberamos leak_int -> LEAK
}

// Función que libera memoria correctamente
void sinLeak() {
    int* temp = new int(42);
    std::cout << "Sin leak: " << *temp << std::endl;
    delete temp; // Correctamente liberado
}

int main() {
    std::cout << "=== INICIO DE PRUEBA DEL MEMORY PROFILER ===\n";

    // 1. LEAK SIMPLE (int)
    int* num = new int(10);
    std::cout << "Numero asignado: " << *num << std::endl;

    // 2. LEAK EN ARRAY (new[])
    double* arr = new double[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 1.1;
    }
    std::cout << "Array asignado: " << arr[0] << ", " << arr[4] << std::endl;

    // 3. LIBERACIÓN CORRECTA (no leak)
    std::string* str = new std::string("Hola Mundo");
    std::cout << "String asignado: " << *str << std::endl;
    delete str; // ✅ Correctamente liberado

    // 4. LEAK EN OTRA FUNCIÓN
    leakEnFuncion();

    // 5. SIN LEAK
    sinLeak();

    // 6. MÁS LEAKS (vector de leaks)
    std::vector<int*> leak_vector;
    for (int i = 0; i < 3; i++) {
        int* dynamic_int = new int(i * 100);
        leak_vector.push_back(dynamic_int);
        std::cout << "Leak vector[" << i << "]: " << *leak_vector[i] << std::endl;
    }
    // NOTA: Liberamos solo algunos para tener leaks mixtos
    delete leak_vector[0]; // ✅ Liberamos uno
    // leak_vector[1] y [2] son LEAKS

    // 7. PRUEBA DE THREAD-SAFETY (opcional)
    std::thread t1([](){
        char* thread_leak = new char('X');
        std::cout << "Leak en thread: " << *thread_leak << std::endl;
        // LEAK: no se libera
    });
    t1.join();

    // 8. LIBERAMOS ALGO MÁS (pero no todo)
    delete num; // ✅ Liberamos el primer leak

    // 9. REPORTE FINAL (debería detectar 5 leaks)
    std::cout << "\n=== REPORTE FINAL ===" << std::endl;
    std::cout << "Memoria total en uso: " << Profiler::tomarMemoriaTotal() << " bytes" << std::endl;
    std::cout << "Asignaciones activas: " << Profiler::tomarCantidadGuardados() << std::endl;

    // Forzar reporte de leaks (normalmente se haría al salir)
    Profiler::ReportarMemoryLeaks();

    return 0;
}