#include "ListaClientes.h"
#include <cctype>
#include <algorithm>

/**
 * @file ListaClientes.cpp
 * @brief Implementación de la clase ListaClientes.
 *
 * Contiene las operaciones principales sobre la lista enlazada simple de clientes:
 * inserción ordenada, búsqueda, eliminación, registro de consumos y generación de tickets.
 */

 // =======================================================
 //  Comparación case-insensitive (usada para ordenar por nombre)
 // =======================================================
int ListaClientes::cmp_ci(const std::string& a, const std::string& b) {
    auto tolow = [](unsigned char c) { return std::tolower(c); };
    size_t n = std::min(a.size(), b.size());
    for (size_t i = 0; i < n; ++i) {
        int da = tolow(a[i]);
        int db = tolow(b[i]);
        if (da != db) return da < db ? -1 : 1;
    }
    if (a.size() == b.size()) return 0;
    return a.size() < b.size() ? -1 : 1;
}

// =======================================================
//  Destructor — libera toda la memoria de la lista
// =======================================================
ListaClientes::~ListaClientes() {
    while (cabeza) {
        auto* t = cabeza;
        cabeza = cabeza->sig;
        delete t;
    }
}

// =======================================================
//  Buscar un nodo por nombre (recorrido lineal)
// =======================================================
ListaClientes::Nodo* ListaClientes::buscarNodo(const std::string& nombre) const {
    Nodo* p = cabeza;
    while (p) {
        if (cmp_ci(p->dato.nombre(), nombre) == 0)
            return p;
        p = p->sig;
    }
    return nullptr;
}

// =======================================================
//  Eliminar un nodo identificado por el nombre del cliente
// =======================================================
bool ListaClientes::eliminarNodo(const std::string& nombre) {
    Nodo* ant = nullptr;
    Nodo* act = cabeza;

    // Buscar el nodo objetivo
    while (act && cmp_ci(act->dato.nombre(), nombre) != 0) {
        ant = act;
        act = act->sig;
    }
    if (!act) return false; // No se encontró

    // Reenlazar punteros
    if (!ant)
        cabeza = act->sig;
    else
        ant->sig = act->sig;

    delete act;
    return true;
}

// =======================================================
//  Insertar cliente manteniendo orden alfabético
// =======================================================
bool ListaClientes::anadirClienteOrdenado(const std::string& nombre, int mesa) {
    if (buscarNodo(nombre)) return false; // Ya existe el cliente

    auto* nuevo = new Nodo(Cliente(nombre, mesa));

    // Insertar al inicio
    if (!cabeza || cmp_ci(nuevo->dato.nombre(), cabeza->dato.nombre()) < 0) {
        nuevo->sig = cabeza;
        cabeza = nuevo;
        return true;
    }

    // Buscar la posición adecuada
    Nodo* p = cabeza;
    while (p->sig && cmp_ci(p->sig->dato.nombre(), nombre) < 0)
        p = p->sig;

    nuevo->sig = p->sig;
    p->sig = nuevo;
    return true;
}

// =======================================================
//  Registrar consumo a un cliente existente
// =======================================================
bool ListaClientes::registrarConsumo(const std::string& nombre, double monto) {
    Nodo* n = buscarNodo(nombre);
    if (!n) return false;
    n->dato.acumular(monto);
    return true;
}

// =======================================================
//  Cobrar y eliminar — genera un Ticket y borra el nodo
// =======================================================
std::optional<Ticket> ListaClientes::cobrarYEliminar(const std::string& nombre) {
    Nodo* n = buscarNodo(nombre);
    if (!n) return std::nullopt;

    // Crear ticket antes de eliminar
    Ticket t(n->dato.nombre(), n->dato.mesa(), n->dato.total());
    eliminarNodo(nombre);
    return t;
}

// =======================================================
//  Recorrer toda la lista aplicando una función visitante
// =======================================================
void ListaClientes::listar(const std::function<void(const Cliente&)>& visit) const {
    for (Nodo* p = cabeza; p; p = p->sig)
        visit(p->dato);
}


