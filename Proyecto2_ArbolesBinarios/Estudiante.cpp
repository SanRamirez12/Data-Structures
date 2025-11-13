#include "Estudiante.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

/**
 * @brief Constructor por defecto de Estudiante.
 * @details
 * Inicializa el id del estudiante en 0 y el promedio en 0.0.
 * El nombre y la carrera se dejan con sus valores por defecto
 * de std::string (cadenas vacías).
 */
Estudiante::Estudiante() : id_(0), promedio_(0.0) {}

/**
 * @brief Constructor que inicializa todos los atributos del estudiante.
 * @param id Identificador único del estudiante.
 * @param nombre Nombre completo del estudiante.
 * @param carrera Carrera o programa académico del estudiante.
 * @param promedio Promedio académico en escala 0.0 - 100.0.
 */
Estudiante::Estudiante(int id, const string& nombre, const string& carrera, double promedio)
    : id_(id), nombre_(nombre), carrera_(carrera), promedio_(promedio) {
}

/**
 * @brief Obtiene el identificador único del estudiante.
 * @return Entero con el id del estudiante.
 */
int Estudiante::id() const { return id_; }

/**
 * @brief Obtiene el nombre del estudiante.
 * @return Referencia constante a la cadena con el nombre del estudiante.
 */
const string& Estudiante::nombre() const { return nombre_; }

/**
 * @brief Obtiene la carrera del estudiante.
 * @return Referencia constante a la cadena con la carrera del estudiante.
 */
const string& Estudiante::carrera() const { return carrera_; }

/**
 * @brief Obtiene el promedio académico del estudiante.
 * @return Valor en punto flotante entre 0.0 y 100.0.
 */
double Estudiante::promedio() const { return promedio_; }

/**
 * @brief Establece el identificador único del estudiante.
 * @param id Nuevo identificador para el estudiante.
 */
void Estudiante::set_id(int id) { id_ = id; }

/**
 * @brief Establece el nombre del estudiante.
 * @param nombre Nueva cadena con el nombre del estudiante.
 */
void Estudiante::set_nombre(const string& nombre) { nombre_ = nombre; }

/**
 * @brief Establece la carrera del estudiante.
 * @param carrera Nueva cadena con la carrera o programa académico del estudiante.
 */
void Estudiante::set_carrera(const string& carrera) { carrera_ = carrera; }

/**
 * @brief Establece el promedio académico del estudiante.
 * @param promedio Nuevo promedio en escala 0.0 - 100.0.
 * @note Se asume que el valor está dentro del rango válido 0.0 - 100.0.
 */
void Estudiante::set_promedio(double promedio) { promedio_ = promedio; }

/**
 * @brief Genera una representación en texto del estudiante.
 * @details
 * Construye una cadena que incluye el id, el nombre, la carrera
 * y el promedio formateado a dos decimales. Es útil para mostrar
 * información en consola o para depuración.
 *
 * Ejemplo de salida:
 * @code
 * ID=1 | Juan Pérez (Ingeniería) | Promedio=89.50
 * @endcode
 *
 * @return Cadena con la información formateada del estudiante.
 */
string Estudiante::a_texto() const {
    ostringstream salida;
    salida << "ID=" << id_ << " | " << nombre_ << " (" << carrera_ << ") | Promedio="
        << fixed << setprecision(2) << promedio_;
    return salida.str();
}

/**
 * @brief Convierte el promedio a una clave entera en centésimas.
 * @details
 * Multiplica el promedio por 100 y aplica un redondeo al entero más cercano.
 * Esto permite representar promedios con dos decimales como un entero,
 * lo cual puede facilitar ordenamientos y manejo en estructuras de datos.
 *
 * Ejemplos:
 * - 87.356 -> 8736
 * - 90.0   -> 9000
 *
 * @param promedio Promedio académico en escala 0.0 - 100.0.
 * @return Entero que representa el promedio escalado a centésimas.
 */
int convertir_promedio_a_clave(double promedio) {
    return static_cast<int>(round(promedio * 100.0));
}

