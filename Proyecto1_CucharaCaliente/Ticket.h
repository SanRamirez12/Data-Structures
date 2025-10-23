#pragma once
#include <string>
#include <filesystem>

/**
 * @class Ticket
 * @brief Representa el comprobante o recibo generado al cobrar a un cliente.
 *
 * Contiene los datos básicos del cliente (nombre, mesa, total) y la fecha/hora
 * en que se emitió. Permite obtener una representación legible del ticket en texto
 * y guardar ese contenido como archivo `.txt` en una carpeta específica.
 *
 * Es una clase de apoyo utilizada por ListaClientes cuando se cobra y elimina
 * un cliente de la lista.
 */
class Ticket {
    std::string nombre_;  ///< Nombre del cliente asociado al ticket.
    int mesa_;            ///< Número de mesa del cliente.
    double total_;        ///< Total cobrado.
    std::string fecha_;   ///< Fecha y hora de emisión (AAAA-MM-DD HH:MM:SS).

    /**
     * @brief Obtiene la fecha y hora actual en formato legible.
     * @return Cadena con formato "AAAA-MM-DD HH:MM:SS".
     */
    static std::string now_string();

    /**
     * @brief Genera una marca de tiempo compacta para usar en el nombre del archivo.
     * @return Cadena con formato "AAAAMMDD_HHMMSS".
     */
    static std::string timestamp_compacto_for_filename();

    /**
     * @brief Sanitiza un texto para que sea seguro como nombre de archivo.
     * Reemplaza o elimina caracteres no válidos.
     */
    static std::string sanitizar(const std::string& s);

public:

    /**
     * @brief Constructor que inicializa un ticket con los datos del cliente.
     * @param nombre Nombre del cliente.
     * @param mesa Número de mesa.
     * @param total Monto total cobrado.
     */
    Ticket(const std::string& nombre, int mesa, double total);

    /// @return Nombre del cliente.
    const std::string& nombre() const { return nombre_; }

    /// @return Número de mesa asociada.
    int mesa() const { return mesa_; }

    /// @return Monto total cobrado.
    double total() const { return total_; }

    /// @return Fecha y hora de emisión.
    const std::string& fecha() const { return fecha_; }

    /**
     * @brief Genera una representación textual legible del ticket.
     * @return Cadena formateada con los datos principales (nombre, mesa, total y fecha).
     */
    std::string texto() const;

    /**
     * @brief Guarda el ticket como archivo .txt en una carpeta dada.
     * @param carpeta Ruta del directorio donde se guardará.
     * @return Ruta completa del archivo creado.
     */
    std::filesystem::path guardarEn(const std::filesystem::path& carpeta) const;
};
