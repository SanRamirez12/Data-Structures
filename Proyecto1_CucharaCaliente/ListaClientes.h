#pragma once
#include <string>
#include <optional>
#include <functional>
#include "Cliente.h"
#include "Ticket.h"

/**
 * @class ListaClientes
 * @brief Implementa una lista enlazada simple de objetos Cliente,
 *        ordenada alfabéticamente por nombre (sin distinción de mayúsculas).
 *
 * Esta clase gestiona dinámicamente los clientes activos del restaurante:
 * permite agregarlos en orden, registrar consumos, cobrar (generar ticket)
 * y eliminarlos de la lista.
 *
 * Cada elemento de la lista es un nodo con un objeto Cliente
 * y un puntero al siguiente nodo.
 */
class ListaClientes {

    /**
     * @struct Nodo
     * @brief Representa un nodo de la lista enlazada.
     *
     * Contiene un objeto Cliente y un puntero al siguiente nodo (sig).
     */
    struct Nodo {
        Cliente dato;   ///< Información del cliente.
        Nodo* sig;      ///< Puntero al siguiente nodo.
        explicit Nodo(const Cliente& c) : dato(c), sig(nullptr) {}
    };

    Nodo* cabeza = nullptr; ///< Puntero al primer nodo de la lista (o nullptr si está vacía).

    /**
     * @brief Compara dos cadenas de texto de forma case-insensitive.
     * @return <0 si a < b, 0 si son iguales, >0 si a > b.
     */
    static int cmp_ci(const std::string& a, const std::string& b);

    /**
     * @brief Busca un nodo que coincida con el nombre dado.
     * @param nombre Nombre del cliente a buscar.
     * @return Puntero al nodo encontrado o nullptr si no existe.
     */
    Nodo* buscarNodo(const std::string& nombre) const;

    /**
     * @brief Elimina un nodo identificado por el nombre del cliente.
     * @param nombre Nombre del cliente a eliminar.
     * @return true si se eliminó correctamente, false si no se encontró.
     */
    bool eliminarNodo(const std::string& nombre);

public:

    ListaClientes() = default; ///< Constructor por defecto.

    /**
     * @brief Destructor. Libera toda la memoria ocupada por los nodos.
     */
    ~ListaClientes();

    // Evita copias de la lista (solo debe existir una instancia viva).
    ListaClientes(const ListaClientes&) = delete;
    ListaClientes& operator=(const ListaClientes&) = delete;

    /**
     * @brief Inserta un nuevo cliente manteniendo el orden alfabético por nombre.
     * @param nombre Nombre del cliente.
     * @param mesa Número de mesa asignado.
     * @return true si se agregó correctamente, false si el nombre ya existe.
     */
    bool anadirClienteOrdenado(const std::string& nombre, int mesa);

    /**
     * @brief Registra un monto de consumo a un cliente existente.
     * @param nombre Nombre del cliente.
     * @param monto Monto a acumular (positivo).
     * @return true si el cliente existe y se actualizó, false en caso contrario.
     */
    bool registrarConsumo(const std::string& nombre, double monto);

    /**
     * @brief Cobra y elimina al cliente de la lista, generando un ticket.
     * @param nombre Nombre del cliente.
     * @return Un Ticket (en std::optional) si el cliente existía;
     *         std::nullopt si no se encontró.
     */
    std::optional<Ticket> cobrarYEliminar(const std::string& nombre);

    /**
     * @brief Recorre la lista aplicando una función visitante a cada cliente.
     * @param visit Función o lambda que recibe una referencia const Cliente&.
     */
    void listar(const std::function<void(const Cliente&)>& visit) const;
};

