#pragma once
#include "Estudiante.h"
#include <functional>

class ArbolBinarioBusqueda {
private:
    struct Nodo {
        int clave_promedio_cent; // promedio en centésimas
        int clave_id;            // desempate por ID
        Estudiante dato;
        Nodo* izquierdo;
        Nodo* derecho;
        explicit Nodo(const Estudiante& estudiante);
    };

    Nodo* raiz_;

    // Utilidades privadas
    static int comparar_claves(int g1, int id1, int g2, int id2);
    static void liberar_postorden(Nodo* nodo);

    // Inserción / búsqueda
    static Nodo* insertar_recursivo(Nodo* nodo, const Estudiante& estudiante);
    static Nodo* buscar_por_promedio_recursivo(Nodo* nodo, int clave_promedio_cent);
    static Nodo* buscar_por_id_recursivo(Nodo* nodo, int id);

    // Recorridos (privados recursivos)
    static void preorden_recursivo(Nodo* nodo, const std::function<void(const Estudiante&)>& visitar);
    static void inorden_recursivo(Nodo* nodo, const std::function<void(const Estudiante&)>& visitar);
    static void postorden_recursivo(Nodo* nodo, const std::function<void(const Estudiante&)>& visitar);

    // Métricas
    static int altura_recursiva(Nodo* nodo);
    static int contar_nodos_recursivo(Nodo* nodo);
    static int contar_hojas_recursivo(Nodo* nodo);

    // Reflejo
    static void reflejar_recursivo(Nodo* nodo);

public:
    ArbolBinarioBusqueda();
    ~ArbolBinarioBusqueda();

    // Operaciones principales
    void insertar(const Estudiante& estudiante);
    const Estudiante* buscar_por_promedio(double promedio); // coincidencia exacta
    const Estudiante* buscar_por_id(int id);                // no está ordenado por ID

    // Recorridos recursivos (públicos)
    void preorden_rec(const std::function<void(const Estudiante&)>& visitar) const;
    void inorden_rec(const std::function<void(const Estudiante&)>& visitar) const;
    void postorden_rec(const std::function<void(const Estudiante&)>& visitar) const;

    // Recorridos iterativos
    void preorden_it(const std::function<void(const Estudiante&)>& visitar) const;
    void inorden_it(const std::function<void(const Estudiante&)>& visitar) const;
    void postorden_it(const std::function<void(const Estudiante&)>& visitar) const;

    // Por niveles (BFS)
    void por_niveles(const std::function<void(const Estudiante&, int nivel)>& visitar) const;

    // Métricas
    int altura() const;
    int contar_nodos() const;
    int contar_hojas() const;
    int contar_internos() const;
    int ancho_maximo() const;

    // Reflejo
    void reflejar();

    // Estado
    bool vacio() const;
};
