#pragma once
#include <string>
#include <functional>
#include <optional>
#include "Cliente.h"
#include "Ticket.h"

class ListaClientes {
    struct Nodo {
        Cliente dato;
        Nodo* sig;
        explicit Nodo(const Cliente& c) : dato(c), sig(nullptr) {}
    };
    Nodo* cabeza = nullptr;

    Nodo* buscarNodo(const std::string& nombre) const;
    bool eliminarNodo(const std::string& nombre);

public:
    ListaClientes() = default;
    ~ListaClientes();
    ListaClientes(const ListaClientes&) = delete;
    ListaClientes& operator=(const ListaClientes&) = delete;

    bool anadirClienteOrdenado(const std::string& nombre, int mesa);
    bool registrarConsumo(const std::string& nombre, double monto);

    // ?? devuelve ticket si existe el cliente; al cobrar lo elimina
    std::optional<Ticket> cobrarYEliminar(const std::string& nombre);

    void listar(const std::function<void(const Cliente&)>& visit) const;
};

