#include "Cliente.h"
#include <stdexcept>

/**
 * @file Cliente.cpp
 * @brief Implementaci�n de la clase Cliente.
 *
 * Define el comportamiento b�sico de un cliente dentro del sistema del restaurante:
 * c�mo se inicializa y c�mo acumula los montos de consumo.
 */

 /**
  * @brief Constructor que inicializa un cliente con su nombre y n�mero de mesa.
  *
  * El total de consumo se inicializa en 0.0 al momento de creaci�n.
  *
  * @param nombre Nombre del cliente.
  * @param mesa N�mero de mesa asignado.
  */
Cliente::Cliente(const std::string& nombre, int mesa)
    : nombre_(nombre), mesa_(mesa), total_(0.0) {
}

/**
 * @brief Acumula un monto positivo en el total del cliente.
 *
 * Lanza una excepci�n si el monto es negativo, para evitar inconsistencias
 * en los registros de consumo.
 *
 * @param monto Monto a agregar al total.
 * @throw std::invalid_argument Si el monto es negativo.
 */
void Cliente::acumular(double monto) {
    if (monto < 0.0)
        throw std::invalid_argument("monto no puede ser negativo");
    total_ += monto;
}
