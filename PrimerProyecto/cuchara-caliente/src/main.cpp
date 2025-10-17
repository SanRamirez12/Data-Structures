#include <iostream>
#include <iomanip>
#include "../encabezados/ListaClientes.h"   
#include "../encabezados/Cliente.h"   


void menu() {
    std::cout << "\n--- LA CUCHARA CALIENTE ---\n"
              << "1) Anadir cliente (ordenado por nombre)\n"
              << "2) Registrar consumo\n"
              << "3) Cobrar (emitir ticket y eliminar)\n"
              << "4) Listar clientes\n"
              << "0) Salir\n> ";
}

int main() {
    ListaClientes lista;
    int op = -1;

    while (true) {
        menu();
        if (!(std::cin >> op)) break;
        if (op == 0) break;

        if (op == 1) {
            std::string nombre; int mesa;
            std::cout << "Nombre: "; std::cin >> std::ws; std::getline(std::cin, nombre);
            std::cout << "Mesa: ";   std::cin >> mesa;
            bool ok = lista.anadirClienteOrdenado(nombre, mesa);
            std::cout << (ok ? "Cliente agregado.\n" : "Ya existe un cliente con ese nombre.\n");
        } else if (op == 2) {
            std::string nombre; double monto;
            std::cout << "Nombre: "; std::cin >> std::ws; std::getline(std::cin, nombre);
            std::cout << "Monto: ";  std::cin >> monto;
            bool ok = lista.registrarConsumo(nombre, monto);
            std::cout << (ok ? "Consumo registrado.\n" : "Cliente no existe.\n");
        } else if (op == 3) {
            std::string nombre;
            std::cout << "Nombre: "; std::cin >> std::ws; std::getline(std::cin, nombre);
            auto t = lista.cobrarYEliminar(nombre);
            if (t.empty()) std::cout << "Cliente no existe.\n";
            else std::cout << "\n" << t;
        } else if (op == 4) {
            std::cout << "\nClientes en atencion (ordenados):\n";
            lista.listar([](const Cliente& c){
                std::cout << " - " << c.nombre()
                          << "  [Mesa " << c.mesa() << "]  Total: "
                          << std::fixed << std::setprecision(2) << c.total() << "\n";
            });
        }
    }
    std::cout << "Adios!\n";
    return 0;
}
