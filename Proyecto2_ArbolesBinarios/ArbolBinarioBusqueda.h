#pragma once
#include "Estudiante.h"
#include <functional>

/**
 * @brief Árbol binario de búsqueda para almacenar estudiantes ordenados por promedio.
 * @details
 * Los nodos del árbol se ordenan principalmente por el promedio del estudiante
 * (expresado en centésimas) y, en caso de empate, por el ID del estudiante.
 * Permite insertar, buscar por promedio o por ID, obtener métricas del árbol,
 * realizar recorridos recursivos e iterativos, y generar el reflejo del árbol.
 */
class ArbolBinarioBusqueda {
private:
    /**
     * @brief Nodo interno del árbol binario de búsqueda.
     * @details
     * Cada nodo almacena:
     * - clave_promedio_cent: promedio en centésimas, usado como clave principal.
     * - clave_id: ID del estudiante, usado como criterio de desempate.
     * - dato: el objeto Estudiante asociado.
     * - punteros al hijo izquierdo y derecho.
     */
    struct Nodo {
        /**
         * @brief Promedio académico del estudiante en centésimas.
         * @details
         * Se utiliza como clave principal de ordenamiento en el árbol.
         * Por ejemplo, un promedio 87.35 se almacena como 8735.
         */
        int clave_promedio_cent; // promedio en centésimas

        /**
         * @brief Identificador único del estudiante.
         * @details
         * Se usa como clave secundaria (desempate) cuando los promedios son iguales.
         */
        int clave_id;            // desempate por ID

        /**
         * @brief Dato almacenado: el estudiante asociado a este nodo.
         */
        Estudiante dato;

        /**
         * @brief Puntero al hijo izquierdo del nodo.
         */
        Nodo* izquierdo;

        /**
         * @brief Puntero al hijo derecho del nodo.
         */
        Nodo* derecho;

        /**
         * @brief Constructor explícito del nodo a partir de un estudiante.
         * @param estudiante Referencia constante al estudiante que se va a almacenar.
         * @details
         * A partir del estudiante se calculan las claves interna de promedio
         * y de ID, y se inicializan los punteros de hijos en nullptr.
         */
        explicit Nodo(const Estudiante& estudiante);
    };

    /**
     * @brief Puntero a la raíz del árbol binario de búsqueda.
     * @details
     * Si el árbol está vacío, este puntero es nullptr.
     */
    Nodo* raiz_;

    // Utilidades privadas

    /**
     * @brief Compara dos pares (promedio, id) como claves del árbol.
     * @param g1 Clave de promedio (centésimas) del primer elemento.
     * @param id1 ID del primer elemento.
     * @param g2 Clave de promedio (centésimas) del segundo elemento.
     * @param id2 ID del segundo elemento.
     * @return
     * - Valor negativo si (g1, id1) < (g2, id2)
     * - 0 si son equivalentes
     * - Valor positivo si (g1, id1) > (g2, id2)
     * @details
     * La comparación se hace primero por promedio; si son iguales,
     * se compara por ID.
     */
    static int comparar_claves(int g1, int id1, int g2, int id2);

    /**
     * @brief Libera todos los nodos del árbol en recorrido postorden.
     * @param nodo Puntero al nodo actual desde el que se inicia la liberación.
     * @details
     * Se usa en el destructor para liberar memoria de forma recursiva
     * desde la raíz.
     */
    static void liberar_postorden(Nodo* nodo);

    // Inserción / búsqueda

    /**
     * @brief Inserta recursivamente un estudiante en el árbol.
     * @param nodo Raíz del subárbol donde se desea insertar.
     * @param estudiante Estudiante a insertar.
     * @return Puntero a la nueva raíz del subárbol tras la inserción.
     * @details
     * Si el nodo es nullptr, se crea uno nuevo. En caso contrario,
     * se decide avanzar a la izquierda o derecha según las claves
     * (promedio en centésimas y ID).
     */
    static Nodo* insertar_recursivo(Nodo* nodo, const Estudiante& estudiante);

    /**
     * @brief Busca recursivamente un estudiante por su promedio (en centésimas).
     * @param nodo Raíz del subárbol donde se realiza la búsqueda.
     * @param clave_promedio_cent Promedio en centésimas a buscar.
     * @return Puntero al nodo encontrado o nullptr si no existe coincidencia.
     * @note La búsqueda es por coincidencia exacta de la clave de promedio.
     */
    static Nodo* buscar_por_promedio_recursivo(Nodo* nodo, int clave_promedio_cent);

    /**
     * @brief Busca recursivamente un estudiante por su ID.
     * @param nodo Raíz del subárbol donde se realiza la búsqueda.
     * @param id ID del estudiante a buscar.
     * @return Puntero al nodo encontrado o nullptr si no se encuentra.
     * @warning El árbol no está ordenado por ID, por lo que esta búsqueda
     *          puede requerir recorrer todo el árbol.
     */
    static Nodo* buscar_por_id_recursivo(Nodo* nodo, int id);

    // Recorridos (privados recursivos)

    /**
     * @brief Recorre el árbol en preorden de manera recursiva.
     * @param nodo Nodo actual en el recorrido.
     * @param visitar Función callback que recibe un Estudiante constante
     *                y se invoca en el orden del recorrido.
     */
    static void preorden_recursivo(Nodo* nodo, const std::function<void(const Estudiante&)>& visitar);

    /**
     * @brief Recorre el árbol en inorden de manera recursiva.
     * @param nodo Nodo actual en el recorrido.
     * @param visitar Función callback para procesar cada estudiante.
     * @details
     * El recorrido inorden visita primero el subárbol izquierdo,
     * luego el nodo actual y finalmente el subárbol derecho, dejando
     * los estudiantes en orden ascendente según su clave.
     */
    static void inorden_recursivo(Nodo* nodo, const std::function<void(const Estudiante&)>& visitar);

    /**
     * @brief Recorre el árbol en postorden de manera recursiva.
     * @param nodo Nodo actual en el recorrido.
     * @param visitar Función callback para procesar cada estudiante.
     */
    static void postorden_recursivo(Nodo* nodo, const std::function<void(const Estudiante&)>& visitar);

    // Métricas

    /**
     * @brief Calcula la altura del árbol de forma recursiva.
     * @param nodo Nodo actual del subárbol.
     * @return Altura del subárbol cuya raíz es nodo.
     * @details
     * Un árbol vacío tiene altura 0. Un árbol con solo la raíz tiene altura 1.
     */
    static int altura_recursiva(Nodo* nodo);

    /**
     * @brief Cuenta el número de nodos en el subárbol de forma recursiva.
     * @param nodo Nodo raíz del subárbol.
     * @return Cantidad total de nodos del subárbol.
     */
    static int contar_nodos_recursivo(Nodo* nodo);

    /**
     * @brief Cuenta el número de hojas en el subárbol de forma recursiva.
     * @param nodo Nodo raíz del subárbol.
     * @return Cantidad de nodos hoja (sin hijos) del subárbol.
     */
    static int contar_hojas_recursivo(Nodo* nodo);

    // Reflejo

    /**
     * @brief Genera el reflejo del subárbol intercambiando hijos izquierdo y derecho.
     * @param nodo Nodo actual del subárbol a reflejar.
     * @details
     * Este proceso se aplica recursivamente a todos los nodos del subárbol.
     */
    static void reflejar_recursivo(Nodo* nodo);

public:
    /**
     * @brief Constructor por defecto del árbol binario de búsqueda.
     * @details
     * Inicializa la raíz en nullptr, indicando que el árbol está vacío.
     */
    ArbolBinarioBusqueda();

    /**
     * @brief Destructor del árbol binario de búsqueda.
     * @details
     * Libera recursivamente todos los nodos del árbol para evitar fugas de memoria.
     */
    ~ArbolBinarioBusqueda();

    // Operaciones principales

    /**
     * @brief Inserta un estudiante en el árbol.
     * @param estudiante Estudiante a insertar.
     * @details
     * El estudiante se ubica de acuerdo con su promedio (convertido a centésimas)
     * y, en caso de empate, según su ID.
     */
    void insertar(const Estudiante& estudiante);

    /**
     * @brief Busca un estudiante por su promedio.
     * @param promedio Promedio académico en escala 0.0 - 100.0.
     * @return Puntero constante al estudiante si se encuentra, o nullptr si no existe.
     * @note La búsqueda se realiza por coincidencia exacta de la clave en centésimas,
     *       es decir, se convierte el promedio con la misma lógica que la inserción.
     */
    const Estudiante* buscar_por_promedio(double promedio); // coincidencia exacta

    /**
     * @brief Busca un estudiante por su ID.
     * @param id Identificador del estudiante a buscar.
     * @return Puntero constante al estudiante si se encuentra, o nullptr si no existe.
     * @warning El árbol no está ordenado por ID, por lo que esta operación puede ser O(n).
     */
    const Estudiante* buscar_por_id(int id);                // no está ordenado por ID

    // Recorridos recursivos (públicos)

    /**
     * @brief Recorre el árbol en preorden de forma recursiva (público).
     * @param visitar Función callback que recibe cada estudiante visitado.
     */
    void preorden_rec(const std::function<void(const Estudiante&)>& visitar) const;

    /**
     * @brief Recorre el árbol en inorden de forma recursiva (público).
     * @param visitar Función callback que se ejecuta para cada estudiante.
     * @details
     * Este recorrido devuelve los estudiantes en orden ascendente de clave.
     */
    void inorden_rec(const std::function<void(const Estudiante&)>& visitar) const;

    /**
     * @brief Recorre el árbol en postorden de forma recursiva (público).
     * @param visitar Función callback para procesar cada estudiante.
     */
    void postorden_rec(const std::function<void(const Estudiante&)>& visitar) const;

    // Recorridos iterativos

    /**
     * @brief Recorre el árbol en preorden de forma iterativa.
     * @param visitar Función callback que se invoca para cada estudiante visitado.
     * @details
     * Implementado usualmente con una pila explícita en lugar de recursión.
     */
    void preorden_it(const std::function<void(const Estudiante&)>& visitar) const;

    /**
     * @brief Recorre el árbol en inorden de forma iterativa.
     * @param visitar Función callback que procesa cada estudiante.
     */
    void inorden_it(const std::function<void(const Estudiante&)>& visitar) const;

    /**
     * @brief Recorre el árbol en postorden de forma iterativa.
     * @param visitar Función callback que procesa cada estudiante.
     */
    void postorden_it(const std::function<void(const Estudiante&)>& visitar) const;

    // Por niveles (BFS)

    /**
     * @brief Recorre el árbol por niveles (BFS).
     * @param visitar Función que recibe el estudiante y el nivel en el que se encuentra.
     * @details
     * El nivel de la raíz suele considerarse 0 o 1 según la implementación interna.
     * Este recorrido facilita visualizar la estructura del árbol por capas.
     */
    void por_niveles(const std::function<void(const Estudiante&, int nivel)>& visitar) const;

    // Métricas

    /**
     * @brief Obtiene la altura del árbol.
     * @return Altura del árbol, donde un árbol vacío tiene altura 0.
     */
    int altura() const;

    /**
     * @brief Cuenta el número total de nodos del árbol.
     * @return Cantidad de nodos almacenados.
     */
    int contar_nodos() const;

    /**
     * @brief Cuenta el número de hojas del árbol.
     * @return Cantidad de nodos hoja (sin hijos).
     */
    int contar_hojas() const;

    /**
     * @brief Cuenta el número de nodos internos del árbol.
     * @return Cantidad de nodos que tienen al menos un hijo.
     */
    int contar_internos() const;

    /**
     * @brief Calcula el ancho máximo del árbol.
     * @return Número máximo de nodos encontrados en un mismo nivel.
     * @details
     * El ancho máximo es útil para estimar el "tamaño horizontal" del árbol.
     */
    int ancho_maximo() const;

    // Reflejo

    /**
     * @brief Genera el reflejo del árbol binario de búsqueda.
     * @details
     * Intercambia recursivamente los hijos izquierdo y derecho de todos
     * los nodos, produciendo una imagen especular del árbol.
     */
    void reflejar();

    // Estado

    /**
     * @brief Verifica si el árbol está vacío.
     * @return true si la raíz es nullptr, false en caso contrario.
     */
    bool vacio() const;
};
