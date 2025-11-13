#pragma once
#include "ArbolBinarioBusqueda.h"

/**
 * @brief Clase de utilidades para manejar la interfaz de usuario y las operaciones sobre el árbol.
 * @details
 * La clase Utils concentra las funciones estáticas que gestionan:
 * - El menú principal de la aplicación.
 * - Las acciones asociadas a cada opción del menú.
 * - La interacción con el usuario para agregar, buscar y listar estudiantes.
 * - La impresión formateada de estudiantes y de recorridos del árbol.
 */
class Utils {
public:
    /**
     * @brief Punto de entrada del flujo de interfaz de usuario (UI).
     * @details
     * Muestra el menú principal en consola y gestiona el ciclo de opciones,
     * delegando en las funciones privadas las acciones correspondientes.
     */
    static void mostrar_menu_principal();

private:
    // Acciones del menú

    /**
     * @brief Ejecuta una demostración predefinida sobre el árbol.
     * @param arbol Referencia al árbol binario de búsqueda a utilizar.
     * @details
     * Suele cargar datos de ejemplo, realizar inserciones y mostrar
     * algunos recorridos para ilustrar el funcionamiento del sistema.
     */
    static void ejecutar_demo(ArbolBinarioBusqueda& arbol);

    /**
     * @brief Permite agregar un nuevo estudiante al árbol.
     * @param arbol Referencia al árbol donde se insertará el estudiante.
     * @details
     * Usualmente solicita los datos del estudiante por consola y los
     * inserta en el árbol con base en su promedio e ID.
     */
    static void agregar_estudiante(ArbolBinarioBusqueda& arbol);

    /**
     * @brief Realiza una búsqueda de estudiante por promedio.
     * @param arbol Referencia al árbol donde se realizará la búsqueda.
     * @details
     * Solicita al usuario un promedio, lo convierte a la clave interna
     * y muestra el estudiante encontrado si existe una coincidencia exacta.
     */
    static void buscar_por_promedio(ArbolBinarioBusqueda& arbol);

    /**
     * @brief Realiza una búsqueda de estudiante por ID.
     * @param arbol Referencia al árbol donde se realizará la búsqueda.
     * @details
     * Pide al usuario un ID y recorre el árbol para localizar al
     * estudiante con dicho identificador, mostrando el resultado.
     */
    static void buscar_por_id(ArbolBinarioBusqueda& arbol);

    /**
     * @brief Lista los estudiantes del árbol utilizando distintos recorridos.
     * @param arbol Referencia al árbol cuyos recorridos se mostrarán.
     * @details
     * Puede invocar recorridos en preorden, inorden, postorden o por niveles,
     * y utilizar funciones de impresión para mostrar cada estudiante.
     */
    static void listar_recorridos(ArbolBinarioBusqueda& arbol);

    /**
     * @brief Muestra métricas del árbol binario de búsqueda.
     * @param arbol Referencia al árbol a analizar.
     * @details
     * Imprime información como altura, número de nodos, hojas, nodos internos
     * y ancho máximo, ayudando a entender la estructura actual del árbol.
     */
    static void mostrar_metricas(ArbolBinarioBusqueda& arbol);

    /**
     * @brief Aplica la operación de reflejo sobre el árbol.
     * @param arbol Referencia al árbol a reflejar.
     * @details
     * Intercambia los subárboles izquierdo y derecho de cada nodo, generando
     * una imagen especular de la estructura original.
     */
    static void reflejar_arbol(ArbolBinarioBusqueda& arbol);

    // Impresión

    /**
     * @brief Imprime la información de un estudiante en formato legible.
     * @param estudiante Referencia constante al estudiante a imprimir.
     * @details
     * Suele delegar en el método a_texto() de Estudiante o construir un
     * formato similar para mostrar su ID, nombre, carrera y promedio.
     */
    static void imprimir_estudiante(const Estudiante& estudiante);

    /**
     * @brief Imprime la información de un estudiante junto con su nivel en el árbol.
     * @param estudiante Referencia constante al estudiante a imprimir.
     * @param nivel Nivel del árbol en el que se encuentra el estudiante.
     * @details
     * Es útil para recorridos por niveles (BFS), donde el nivel indica la
     * profundidad relativa del nodo dentro del árbol.
     */
    static void imprimir_estudiante_con_nivel(const Estudiante& estudiante, int nivel);
};

