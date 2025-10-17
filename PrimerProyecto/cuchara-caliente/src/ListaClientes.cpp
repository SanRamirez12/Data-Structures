#include "../encabezados/ListaClientes.h"
#include <cctype>
#include <algorithm>

static int cmp_ci(const std::string& a, const std::string& b) {
    auto tolow = [](unsigned char c){ return std::tolower(c); };
    size_t n = std::min(a.size(), b.size());
    for (size_t i = 0; i < n; ++i) {
        int da = tolow(a[i]);
        int db = tolow(b[i]);
        if (da != db) return da < db ? -1 : 1;
    }
    if (a.size() == b.size()) return 0;
    return a.size() < b.size() ? -1 : 1;
}

ListaClientes::~ListaClientes() {
    while (cabeza) {
        auto* t = cabeza;
        cabeza = cabeza->sig;
        delete t;
    }
}

ListaClientes::Nodo* ListaClientes::buscarNodo(const std::string& nombre) const {
    auto* p = cabeza;
    while (p) {
        if (cmp_ci(p->dato.nombre(), nombre) == 0) return p;
        p = p->sig;
    }
    return nullptr;
}

bool ListaClientes::eliminarNodo(const std::string& nombre) {
    Nodo* ant = nullptr;
    Nodo* act = cabeza;
    while (act && cmp_ci(act->dato.nombre(), nombre) != 0) {
        ant = act;
        act = act->sig;
    }
    if (!act) return false;
    if (!ant) cabeza = act->sig; else ant->sig = act->sig;
    delete act;
    return true;
}

bool ListaClientes::anadirClienteOrdenado(const std::string& nombre, int mesa) {
    if (buscarNodo(nombre)) return false;
    auto* nuevo = new Nodo(Cliente(nombre, mesa));

    if (!cabeza || cmp_ci(nombre, cabeza->dato.nombre()) < 0) {
        nuevo->sig = cabeza;
        cabeza = nuevo;
        return true;
    }
    auto* p = cabeza;
    while (p->sig && cmp_ci(p->sig->dato.nombre(), nombre) < 0) p = p->sig;
    nuevo->sig = p->sig;
    p->sig = nuevo;
    return true;
}

bool ListaClientes::registrarConsumo(const std::string& nombre, double monto) {
    auto* n = buscarNodo(nombre);
    if (!n) return false;
    n->dato.acumular(monto);
    return true;
}

std::string ListaClientes::cobrarYEliminar(const std::string& nombre) {
    auto* n = buscarNodo(nombre);
    if (!n) return {};
    std::string t = n->dato.ticket();
    eliminarNodo(nombre);
    return t;
}

void ListaClientes::listar(const std::function<void(const Cliente&)>& visit) const {
    auto* p = cabeza;
    while (p) { visit(p->dato); p = p->sig; }
}

