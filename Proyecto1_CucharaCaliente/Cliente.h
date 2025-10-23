#pragma once
#include <string>

/**
 * @class Cliente
 * @brief Representa a un cliente atendido en el restaurante.
 *
 * Cada cliente tiene un nombre, un número de mesa y un total acumulado
 * correspondiente al consumo registrado durante su estancia.
 *
 * Esta clase funciona como unidad básica de información dentro de la
 * lista enlazada gestionada por la clase ListaClientes.
 */
class Cliente {
    std::string nombre_;  ///< Nombre del cliente.
    int mesa_;            ///< Número de mesa asignado.
    double total_;        ///< Total acumulado del consumo del cliente.

public:
    /**
     * @brief Constructor que inicializa un cliente con nombre y mesa.
     * @param nombre Nombre del cliente.
     * @param mesa Número de mesa asignado.
     */
    Cliente(const std::string& nombre, int mesa);

    /// @return Nombre del cliente.
    const std::string& nombre() const { return nombre_; }

    /// @return Número de mesa asignado.
    int mesa() const { return mesa_; }

    /// @return Total acumulado del cliente.
    double total() const { return total_; }

    /**
     * @brief Acumula un monto positivo al total del cliente.
     * @param monto Monto a sumar. Debe ser positivo.
     */
    void acumular(double monto);
};

