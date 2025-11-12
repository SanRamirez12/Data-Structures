#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

void Utils::imprimir_estudiante(const Estudiante& estudiante) {
    cout << estudiante.a_texto() << "\n";
}

void Utils::imprimir_estudiante_con_nivel(const Estudiante& estudiante, int nivel) {
    cout << "[Nivel " << nivel << "] " << estudiante.a_texto() << "\n";
}

void Utils::ejecutar_demo(ArbolBinarioBusqueda& arbol) {
    cout << "\n=== DEMO: promedios 50,30,70,20,40,60,80 ===\n";
    int ids_demo[7] = { 101,102,103,104,105,106,107 };
    double promedios_demo[7] = { 50,30,70,20,40,60,80 };
    string nombres_demo[7] = { "Ana","Beto","Carla","Diego","Elena","Fabio","Gina" };
    for (int indice = 0; indice < 7; ++indice) {
        arbol.insertar(Estudiante(ids_demo[indice], nombres_demo[indice], "Ingeniería", promedios_demo[indice]));
    }

    cout << "\n- InOrden (recursivo):\n";
    arbol.inorden_rec(imprimir_estudiante);

    cout << "\n- PreOrden (rec / it):\n";
    arbol.preorden_rec(imprimir_estudiante);
    cout << "---\n";
    arbol.preorden_it(imprimir_estudiante);

    cout << "\n- PostOrden (rec / it):\n";
    arbol.postorden_rec(imprimir_estudiante);
    cout << "---\n";
    arbol.postorden_it(imprimir_estudiante);

    cout << "\n- Por niveles (BFS):\n";
    arbol.por_niveles([](const Estudiante& estudiante, int nivel) {
        Utils::imprimir_estudiante_con_nivel(estudiante, nivel);
        });

    cout << "\n- Métricas:\n";
    cout << "Altura: " << arbol.altura() << "\n";
    cout << "Nodos totales: " << arbol.contar_nodos() << "\n";
    cout << "Hojas: " << arbol.contar_hojas() << "\n";
    cout << "Internos: " << arbol.contar_internos() << "\n";
    cout << "Ancho máximo: " << arbol.ancho_maximo() << "\n";

    cout << "\n- Reflejar e imprimir InOrden (invertido):\n";
    arbol.reflejar();
    arbol.inorden_rec(imprimir_estudiante);

    // Restaurar a su forma original
    arbol.reflejar();
}

void Utils::agregar_estudiante(ArbolBinarioBusqueda& arbol) {
    int id_ingresado;
    string nombre_ingresado;
    string carrera_ingresada;
    double promedio_ingresado;

    cout << "ID (entero): ";
    cin >> id_ingresado;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre: ";
    getline(cin, nombre_ingresado);

    cout << "Carrera: ";
    getline(cin, carrera_ingresada);

    cout << "Promedio (0-100): ";
    cin >> promedio_ingresado;

    arbol.insertar(Estudiante(id_ingresado, nombre_ingresado, carrera_ingresada, promedio_ingresado));
    cout << "-> Estudiante insertado.\n";
}

void Utils::buscar_por_promedio(ArbolBinarioBusqueda& arbol) {
    double promedio_busqueda;
    cout << "Promedio exacto a buscar: ";
    cin >> promedio_busqueda;

    const Estudiante* resultado = arbol.buscar_por_promedio(promedio_busqueda);
    if (resultado != nullptr) {
        cout << "Encontrado: " << resultado->a_texto() << "\n";
    }
    else {
        cout << "No hay estudiantes con ese promedio exacto.\n";
    }
}

void Utils::buscar_por_id(ArbolBinarioBusqueda& arbol) {
    int id_busqueda;
    cout << "ID a buscar: ";
    cin >> id_busqueda;

    const Estudiante* resultado = arbol.buscar_por_id(id_busqueda);
    if (resultado != nullptr) {
        cout << "Encontrado: " << resultado->a_texto() << "\n";
    }
    else {
        cout << "No se encontró el ID indicado.\n";
    }
}

void Utils::listar_recorridos(ArbolBinarioBusqueda& arbol) {
    int opcion_listado;
    cout << "\nListar:\n"
        << "1) InOrden (recursivo)\n"
        << "2) PreOrden (recursivo)\n"
        << "3) PostOrden (recursivo)\n"
        << "4) InOrden (iterativo)\n"
        << "5) PreOrden (iterativo)\n"
        << "6) PostOrden (iterativo)\n"
        << "7) Por niveles (BFS)\n"
        << "Opción: ";
    cin >> opcion_listado;

    cout << "\n--- Listado ---\n";
    switch (opcion_listado) {
    case 1: arbol.inorden_rec(imprimir_estudiante); break;
    case 2: arbol.preorden_rec(imprimir_estudiante); break;
    case 3: arbol.postorden_rec(imprimir_estudiante); break;
    case 4: arbol.inorden_it(imprimir_estudiante); break;
    case 5: arbol.preorden_it(imprimir_estudiante); break;
    case 6: arbol.postorden_it(imprimir_estudiante); break;
    case 7:
        arbol.por_niveles([](const Estudiante& estudiante, int nivel) {
            Utils::imprimir_estudiante_con_nivel(estudiante, nivel);
            });
        break;
    default:
        cout << "Opción inválida.\n";
        break;
    }
}

void Utils::mostrar_metricas(ArbolBinarioBusqueda& arbol) {
    cout << "\nMétricas del árbol:\n";
    cout << "Altura: " << arbol.altura() << "\n";
    cout << "Nodos totales: " << arbol.contar_nodos() << "\n";
    cout << "Hojas: " << arbol.contar_hojas() << "\n";
    cout << "Internos: " << arbol.contar_internos() << "\n";
    cout << "Ancho máximo: " << arbol.ancho_maximo() << "\n";
}

void Utils::reflejar_arbol(ArbolBinarioBusqueda& arbol) {
    arbol.reflejar();
    cout << "-> Árbol reflejado.\n";
}

void Utils::mostrar_menu_principal() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ArbolBinarioBusqueda arbol;
    int opcion_menu;
    do {
        cout << "\n==== Gestor de Estudiantes (BST) ====\n"
            << "1) DEMO (insertar 7 promedios y mostrar todo)\n"
            << "2) Agregar estudiante\n"
            << "3) Buscar por promedio\n"
            << "4) Buscar por ID\n"
            << "5) Listar (DFS/BFS)\n"
            << "6) Ver métricas\n"
            << "7) Reflejar árbol\n"
            << "0) Salir\n"
            << "Opción: ";
        cin >> opcion_menu;

        switch (opcion_menu) {
        case 1: ejecutar_demo(arbol); break;
        case 2: agregar_estudiante(arbol); break;
        case 3: buscar_por_promedio(arbol); break;
        case 4: buscar_por_id(arbol); break;
        case 5: listar_recorridos(arbol); break;
        case 6: mostrar_metricas(arbol); break;
        case 7: reflejar_arbol(arbol); break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion_menu != 0);
}
