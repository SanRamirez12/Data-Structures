#pragma once
#include <string>

/**
 * @brief Representa a un estudiante con datos básicos.
 * @details
 * Contiene un identificador único, nombre, carrera y el promedio
 * en una escala de 0.0 a 100.0. Se utiliza como entidad principal
 * para almacenar y manipular la información académica de un estudiante.
 */
class Estudiante {
private:
    /**
     * @brief Identificador único del estudiante.
     */
    int id_;

    /**
     * @brief Nombre completo del estudiante.
     */
    std::string nombre_;

    /**
     * @brief Carrera o programa académico del estudiante.
     */
    std::string carrera_;

    /**
     * @brief Promedio académico del estudiante en escala 0.0 - 100.0.
     */
    double promedio_; // 0.0 - 100.0

public:
    /**
     * @brief Constructor por defecto.
     * @details
     * Inicializa un estudiante con valores neutros/por defecto.
     * La implementación concreta se define en el archivo .cpp.
     */
    Estudiante();

    /**
     * @brief Constructor que inicializa todos los atributos del estudiante.
     * @param id Identificador único del estudiante.
     * @param nombre Nombre completo del estudiante.
     * @param carrera Carrera o programa académico del estudiante.
     * @param promedio Promedio académico en escala 0.0 - 100.0.
     */
    Estudiante(int id, const std::string& nombre, const std::string& carrera, double promedio);

    // Getters

    /**
     * @brief Obtiene el identificador único del estudiante.
     * @return Entero que representa el id del estudiante.
     */
    int id() const;

    /**
     * @brief Obtiene el nombre del estudiante.
     * @return Referencia constante a la cadena con el nombre.
     */
    const std::string& nombre() const;

    /**
     * @brief Obtiene la carrera del estudiante.
     * @return Referencia constante a la cadena con la carrera.
     */
    const std::string& carrera() const;

    /**
     * @brief Obtiene el promedio académico del estudiante.
     * @return Valor en punto flotante entre 0.0 y 100.0.
     */
    double promedio() const;

    // Setters

    /**
     * @brief Establece el identificador único del estudiante.
     * @param id Nuevo identificador para el estudiante.
     */
    void set_id(int id);

    /**
     * @brief Establece el nombre del estudiante.
     * @param nombre Nueva cadena con el nombre del estudiante.
     */
    void set_nombre(const std::string& nombre);

    /**
     * @brief Establece la carrera del estudiante.
     * @param carrera Nueva cadena con la carrera o programa académico.
     */
    void set_carrera(const std::string& carrera);

    /**
     * @brief Establece el promedio académico del estudiante.
     * @param promedio Nuevo promedio en escala 0.0 - 100.0.
     * @note Es responsabilidad de quien llama garantizar que el valor
     *       esté dentro del rango válido.
     */
    void set_promedio(double promedio);

    /**
     * @brief Genera una representación en texto del estudiante.
     * @details
     * Suele utilizarse para mostrar la información en consola o para
     * depuración, formateando los campos del estudiante en una cadena.
     * @return Cadena con la información relevante del estudiante.
     */
    std::string a_texto() const;
};

/**
 * @brief Convierte un promedio en una clave entera en centésimas.
 * @details
 * Toma un valor de promedio en punto flotante (0.0 - 100.0) y lo escala
 * a un entero en centésimas para facilitar operaciones como ordenamiento
 * o uso como clave en estructuras de datos.
 *
 * Ejemplo:
 * - 87.356 -> 8736 (aprox.)
 *
 * @param promedio Promedio académico en escala 0.0 - 100.0.
 * @return Entero que representa el promedio escalado a centésimas.
 */
int convertir_promedio_a_clave(double promedio);


