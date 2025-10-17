// Proyecto1_CucharaCaliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <filesystem>
#include "ListaClientes.h"

namespace fs = std::filesystem;

// ====================== utilidades de entrada ======================
int leerInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Intenta de nuevo.\n";
    }
}
double leerDouble(const std::string& prompt) {
    double v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida. Intenta de nuevo.\n";
    }
}
std::string leerLinea(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}
void pausar() {
    std::cout << "\nPresiona ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ====================== UI ======================
void menu() {
    std::cout << "\n=== LA CUCHARA CALIENTE ===\n"
        << "1) Anadir cliente (ordenado por nombre)\n"
        << "2) Registrar consumo\n"
        << "3) Cobrar (emitir ticket, guardar y eliminar)\n"
        << "4) Listar clientes\n"
        << "0) Salir\n";
}

int main() {
    ListaClientes lista;
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(2);

    while (true) {
        menu();
        int op = leerInt("> ");
        if (op == 0) { std::cout << "Adios!\n"; break; }

        switch (op) {
        case 1: {
            std::string nombre = leerLinea("Nombre: ");
            int mesa = leerInt("Mesa: ");
            bool ok = lista.anadirClienteOrdenado(nombre, mesa);
            std::cout << (ok ? "Cliente agregado.\n" : "Ya existe un cliente con ese nombre.\n");
            pausar(); break;
        }
        case 2: {
            std::string nombre = leerLinea("Nombre: ");
            double monto = leerDouble("Monto: ");
            bool ok = lista.registrarConsumo(nombre, monto);
            std::cout << (ok ? "Consumo registrado.\n" : "Cliente no existe.\n");
            pausar(); break;
        }
        case 3: {
            std::string nombre = leerLinea("Nombre: ");
            auto t = lista.cobrarYEliminar(nombre);
            if (!t.has_value()) {
                std::cout << "Cliente no existe.\n";
            }
            else {
                std::cout << "\n" << t->texto();
                auto ruta = t->guardarEn("tickets"); // carpeta relativa
                std::cout << "Ticket guardado en: " << ruta.string() << "\n";
            }
            pausar(); break;
        }
        case 4: {
            std::cout << "\nClientes en atencion (ordenados):\n";
            lista.listar([](const Cliente& c) {
                std::cout << " - " << c.nombre()
                    << "  [Mesa " << c.mesa() << "]  Total: "
                    << c.total() << "\n";
                });
            pausar(); break;
        }
        default:
            std::cout << "Opcion invalida.\n"; pausar(); break;
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
