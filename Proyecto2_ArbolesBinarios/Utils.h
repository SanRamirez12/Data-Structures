#pragma once
#include "ArbolBinarioBusqueda.h"

class Utils {
public:
    // Punto de entrada del flujo de UI
    static void mostrar_menu_principal();

private:
    // Acciones del menú
    static void ejecutar_demo(ArbolBinarioBusqueda& arbol);
    static void agregar_estudiante(ArbolBinarioBusqueda& arbol);
    static void buscar_por_promedio(ArbolBinarioBusqueda& arbol);
    static void buscar_por_id(ArbolBinarioBusqueda& arbol);
    static void listar_recorridos(ArbolBinarioBusqueda& arbol);
    static void mostrar_metricas(ArbolBinarioBusqueda& arbol);
    static void reflejar_arbol(ArbolBinarioBusqueda& arbol);

    // Impresión
    static void imprimir_estudiante(const Estudiante& estudiante);
    static void imprimir_estudiante_con_nivel(const Estudiante& estudiante, int nivel);
};

