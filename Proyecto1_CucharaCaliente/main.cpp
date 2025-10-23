// Proyecto1_CucharaCaliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include "ListaClientes.h"

using std::cout; using std::cin; using std::string;

/**
 * @file main.cpp
 * @brief Punto de entrada del programa "La Cuchara Caliente".
 *
 * Este archivo implementa una interfaz de consola interactiva que permite:
 *  - Agregar clientes (ordenados por nombre)
 *  - Registrar consumos individuales
 *  - Cobrar y generar tickets
 *  - Listar los clientes activos
 *
 * Internamente, utiliza la clase ListaClientes, que a su vez administra
 * una lista enlazada simple de objetos Cliente.
 *
 * El programa se ejecuta en bucle hasta que el usuario elige la opción 0 (Salir).
 */

 // =======================================================
 //  Funciones auxiliares para entrada de datos validada
 // =======================================================

 /**
  * @brief Elimina espacios en blanco al inicio y final de una cadena.
  */
static inline string trim(string s) {
    auto issp = [](unsigned char c) { return std::isspace(c); };
    while (!s.empty() && issp(s.front())) s.erase(s.begin());
    while (!s.empty() && issp(s.back()))  s.pop_back();
    return s;
}

/**
 * @brief Lee una línea completa del usuario (incluyendo espacios).
 */
static inline string leerLinea(const string& prompt) {
    cout << prompt;
    string s;
    std::getline(cin, s);
    return s;
}

/**
 * @brief Lee un número entero validando errores y repreguntando.
 */
static int leerInt(const string& prompt) {
    for (;;) {
        string s = trim(leerLinea(prompt));
        if (s.empty()) { cout << "Valor vacío. Intente de nuevo.\n"; continue; }
        try {
            size_t pos = 0;
            long v = std::stol(s, &pos, 10);
            if (pos != s.size()) throw std::invalid_argument("resto");
            if (v < std::numeric_limits<int>::min() || v > std::numeric_limits<int>::max())
                throw std::out_of_range("rango");
            return static_cast<int>(v);
        }
        catch (...) {
            cout << "Valor inválido. Intente de nuevo.\n";
        }
    }
}

/**
 * @brief Lee un número real (double) validando el formato de entrada.
 */
static double leerDouble(const string& prompt) {
    for (;;) {
        string s = trim(leerLinea(prompt));
        if (s.empty()) { cout << "Valor vacío. Intente de nuevo.\n"; continue; }
        try {
            size_t pos = 0;
            double v = std::stod(s, &pos);
            if (pos != s.size()) throw std::invalid_argument("resto");
            return v;
        }
        catch (...) {
            cout << "Valor inválido. Intente de nuevo.\n";
        }
    }
}

/**
 * @brief Detiene la ejecución temporalmente hasta presionar ENTER.
 */
static void pausar() {
    cout << "\nPresiona ENTER para continuar...";
    std::string dummy;
    std::getline(cin, dummy);
}

// =======================================================
//  Interfaz de usuario (menú principal)
// =======================================================
static void menu() {
    cout << "\n=== MENU ===\n"
        "1) Agregar cliente\n"
        "2) Registrar consumo\n"
        "3) Cobrar y eliminar (genera ticket)\n"
        "4) Listar clientes\n"
        "0) Salir\n";
}

// =======================================================
//  Función principal
// =======================================================
int main() {
    ListaClientes lista;                   // Estructura principal de almacenamiento
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(2);     // Mostrar montos con 2 decimales

    bool run = true;
    while (run) {
        menu();                            // Mostrar menú principal
        int op = leerInt("Opcion: ");      // Leer opción del usuario

        switch (op) {
        case 1: {  // Agregar cliente
            string nombre = leerLinea("Nombre: ");
            int mesa = leerInt("Mesa: ");
            bool ok = lista.anadirClienteOrdenado(nombre, mesa);
            cout << (ok ? "Cliente agregado.\n" : "Ya existe un cliente con ese nombre.\n");
            pausar();
            break;
        }
        case 2: {  // Registrar consumo
            string nombre = leerLinea("Nombre: ");
            double monto = leerDouble("Monto: ");
            bool ok = lista.registrarConsumo(nombre, monto);
            cout << (ok ? "Consumo registrado.\n" : "Cliente no existe.\n");
            pausar();
            break;
        }
        case 3: {  // Cobrar y eliminar cliente
            string nombre = leerLinea("Nombre: ");
            auto t = lista.cobrarYEliminar(nombre);
            if (!t.has_value()) {
                cout << "Cliente no existe.\n";
            }
            else {
                cout << "\n" << t->texto(); // Mostrar ticket en consola
                auto ruta = t->guardarEn("tickets"); // Guardar ticket en archivo .txt
                cout << "Ticket guardado en: " << ruta.string() << "\n";
            }
            pausar();
            break;
        }
        case 4: {  // Listar todos los clientes
            cout << "\nClientes en atención (ordenados):\n";
            lista.listar([](const Cliente& c) {
                cout << " - " << c.nombre()
                    << "  [Mesa " << c.mesa()
                    << "]  Total: " << c.total() << "\n";
                });
            pausar();
            break;
        }
        case 0:    // Salir del programa
            run = false;
            break;
        default:   // Opción inválida
            cout << "Opcion invalida.\n";
            pausar();
            break;
        }
    }
    return 0;
}



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
