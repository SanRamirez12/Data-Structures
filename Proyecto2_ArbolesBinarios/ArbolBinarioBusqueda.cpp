#include "ArbolBinarioBusqueda.h"
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// ---------- Nodo ----------
ArbolBinarioBusqueda::Nodo::Nodo(const Estudiante& estudiante)
    : clave_promedio_cent(convertir_promedio_a_clave(estudiante.promedio())),
    clave_id(estudiante.id()),
    dato(estudiante),
    izquierdo(nullptr),
    derecho(nullptr) {
}

// ---------- Constructor / Destructor ----------
ArbolBinarioBusqueda::ArbolBinarioBusqueda() : raiz_(nullptr) {}

ArbolBinarioBusqueda::~ArbolBinarioBusqueda() {
    liberar_postorden(raiz_);
    raiz_ = nullptr;
}

// ---------- Utilidades privadas ----------
int ArbolBinarioBusqueda::comparar_claves(int g1, int id1, int g2, int id2) {
    if (g1 < g2) return -1;
    if (g1 > g2) return 1;
    if (id1 < id2) return -1;
    if (id1 > id2) return 1;
    return 0;
}

void ArbolBinarioBusqueda::liberar_postorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    liberar_postorden(nodo->izquierdo);
    liberar_postorden(nodo->derecho);
    delete nodo;
}

// ---------- Inserción / Búsqueda ----------
ArbolBinarioBusqueda::Nodo* ArbolBinarioBusqueda::insertar_recursivo(Nodo* nodo, const Estudiante& estudiante) {
    if (nodo == nullptr) return new Nodo(estudiante);
    const int clave_promedio_nuevo = convertir_promedio_a_clave(estudiante.promedio());
    const int comparacion = comparar_claves(clave_promedio_nuevo, estudiante.id(), nodo->clave_promedio_cent, nodo->clave_id);

    if (comparacion < 0) {
        nodo->izquierdo = insertar_recursivo(nodo->izquierdo, estudiante);
    }
    else if (comparacion > 0) {
        nodo->derecho = insertar_recursivo(nodo->derecho, estudiante);
    }
    else {
        nodo->dato = estudiante; // misma clave: actualiza
    }
    return nodo;
}

void ArbolBinarioBusqueda::insertar(const Estudiante& estudiante) {
    raiz_ = insertar_recursivo(raiz_, estudiante);
}

ArbolBinarioBusqueda::Nodo* ArbolBinarioBusqueda::buscar_por_promedio_recursivo(Nodo* nodo, int clave_promedio_cent) {
    if (nodo == nullptr) return nullptr;
    if (clave_promedio_cent < nodo->clave_promedio_cent) return buscar_por_promedio_recursivo(nodo->izquierdo, clave_promedio_cent);
    if (clave_promedio_cent > nodo->clave_promedio_cent) return buscar_por_promedio_recursivo(nodo->derecho, clave_promedio_cent);
    return nodo; // primer match del promedio
}

const Estudiante* ArbolBinarioBusqueda::buscar_por_promedio(double promedio) {
    const int clave_busqueda = convertir_promedio_a_clave(promedio);
    Nodo* nodo_encontrado = buscar_por_promedio_recursivo(raiz_, clave_busqueda);
    return nodo_encontrado ? &nodo_encontrado->dato : nullptr;
}

ArbolBinarioBusqueda::Nodo* ArbolBinarioBusqueda::buscar_por_id_recursivo(Nodo* nodo, int id) {
    if (nodo == nullptr) return nullptr;
    if (nodo->dato.id() == id) return nodo;

    Nodo* resultado_izquierdo = buscar_por_id_recursivo(nodo->izquierdo, id);
    if (resultado_izquierdo != nullptr) return resultado_izquierdo;

    return buscar_por_id_recursivo(nodo->derecho, id);
}

const Estudiante* ArbolBinarioBusqueda::buscar_por_id(int id) {
    Nodo* nodo_encontrado = buscar_por_id_recursivo(raiz_, id);
    return nodo_encontrado ? &nodo_encontrado->dato : nullptr;
}

// ---------- Recorridos recursivos (públicos) ----------
void ArbolBinarioBusqueda::preorden_rec(const function<void(const Estudiante&)>& visitar) const {
    preorden_recursivo(raiz_, visitar);
}
void ArbolBinarioBusqueda::inorden_rec(const function<void(const Estudiante&)>& visitar) const {
    inorden_recursivo(raiz_, visitar);
}
void ArbolBinarioBusqueda::postorden_rec(const function<void(const Estudiante&)>& visitar) const {
    postorden_recursivo(raiz_, visitar);
}

// ---------- Recorridos recursivos (privados) ----------
void ArbolBinarioBusqueda::preorden_recursivo(Nodo* nodo, const function<void(const Estudiante&)>& visitar) {
    if (nodo == nullptr) return;
    visitar(nodo->dato);
    preorden_recursivo(nodo->izquierdo, visitar);
    preorden_recursivo(nodo->derecho, visitar);
}
void ArbolBinarioBusqueda::inorden_recursivo(Nodo* nodo, const function<void(const Estudiante&)>& visitar) {
    if (nodo == nullptr) return;
    inorden_recursivo(nodo->izquierdo, visitar);
    visitar(nodo->dato);
    inorden_recursivo(nodo->derecho, visitar);
}
void ArbolBinarioBusqueda::postorden_recursivo(Nodo* nodo, const function<void(const Estudiante&)>& visitar) {
    if (nodo == nullptr) return;
    postorden_recursivo(nodo->izquierdo, visitar);
    postorden_recursivo(nodo->derecho, visitar);
    visitar(nodo->dato);
}

// ---------- Recorridos iterativos ----------
void ArbolBinarioBusqueda::preorden_it(const function<void(const Estudiante&)>& visitar) const {
    if (raiz_ == nullptr) return;
    stack<Nodo*> pila_nodos;
    pila_nodos.push(raiz_);
    while (!pila_nodos.empty()) {
        Nodo* nodo_actual = pila_nodos.top(); pila_nodos.pop();
        visitar(nodo_actual->dato);
        if (nodo_actual->derecho) pila_nodos.push(nodo_actual->derecho);
        if (nodo_actual->izquierdo) pila_nodos.push(nodo_actual->izquierdo);
    }
}

void ArbolBinarioBusqueda::inorden_it(const function<void(const Estudiante&)>& visitar) const {
    stack<Nodo*> pila_nodos;
    Nodo* nodo_actual = raiz_;
    while (nodo_actual != nullptr || !pila_nodos.empty()) {
        while (nodo_actual != nullptr) { pila_nodos.push(nodo_actual); nodo_actual = nodo_actual->izquierdo; }
        nodo_actual = pila_nodos.top(); pila_nodos.pop();
        visitar(nodo_actual->dato);
        nodo_actual = nodo_actual->derecho;
    }
}

void ArbolBinarioBusqueda::postorden_it(const function<void(const Estudiante&)>& visitar) const {
    if (raiz_ == nullptr) return;
    stack<Nodo*> pila_entrada, pila_salida;
    pila_entrada.push(raiz_);
    while (!pila_entrada.empty()) {
        Nodo* nodo_actual = pila_entrada.top(); pila_entrada.pop();
        pila_salida.push(nodo_actual);
        if (nodo_actual->izquierdo) pila_entrada.push(nodo_actual->izquierdo);
        if (nodo_actual->derecho) pila_entrada.push(nodo_actual->derecho);
    }
    while (!pila_salida.empty()) { visitar(pila_salida.top()->dato); pila_salida.pop(); }
}

// ---------- Por niveles (BFS) ----------
void ArbolBinarioBusqueda::por_niveles(const function<void(const Estudiante&, int)>& visitar) const {
    if (raiz_ == nullptr) return;
    queue<pair<Nodo*, int>> cola_niveles;
    cola_niveles.push({ raiz_, 0 });
    while (!cola_niveles.empty()) {
        Nodo* nodo_actual = cola_niveles.front().first;
        int nivel_actual = cola_niveles.front().second;
        cola_niveles.pop();

        visitar(nodo_actual->dato, nivel_actual);

        if (nodo_actual->izquierdo) cola_niveles.push({ nodo_actual->izquierdo, nivel_actual + 1 });
        if (nodo_actual->derecho)  cola_niveles.push({ nodo_actual->derecho,  nivel_actual + 1 });
    }
}

// ---------- Métricas ----------
int ArbolBinarioBusqueda::altura_recursiva(Nodo* nodo) {
    if (nodo == nullptr) return -1; // árbol vacío = -1; un nodo = 0
    int altura_izquierda = altura_recursiva(nodo->izquierdo);
    int altura_derecha = altura_recursiva(nodo->derecho);
    return 1 + std::max(altura_izquierda, altura_derecha);
}
int ArbolBinarioBusqueda::altura() const { return altura_recursiva(raiz_); }

int ArbolBinarioBusqueda::contar_nodos_recursivo(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contar_nodos_recursivo(nodo->izquierdo) + contar_nodos_recursivo(nodo->derecho);
}
int ArbolBinarioBusqueda::contar_nodos() const { return contar_nodos_recursivo(raiz_); }

int ArbolBinarioBusqueda::contar_hojas_recursivo(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
    return contar_hojas_recursivo(nodo->izquierdo) + contar_hojas_recursivo(nodo->derecho);
}
int ArbolBinarioBusqueda::contar_hojas() const { return contar_hojas_recursivo(raiz_); }

int ArbolBinarioBusqueda::contar_internos() const {
    return contar_nodos() - contar_hojas();
}

int ArbolBinarioBusqueda::ancho_maximo() const {
    if (raiz_ == nullptr) return 0;
    queue<Nodo*> cola_nodos;
    cola_nodos.push(raiz_);
    int ancho_mayor = 0;

    while (!cola_nodos.empty()) {
        int nodos_en_nivel = static_cast<int>(cola_nodos.size());
        ancho_mayor = std::max(ancho_mayor, nodos_en_nivel);

        for (int indice = 0; indice < nodos_en_nivel; ++indice) {
            Nodo* nodo_actual = cola_nodos.front(); cola_nodos.pop();
            if (nodo_actual->izquierdo) cola_nodos.push(nodo_actual->izquierdo);
            if (nodo_actual->derecho)  cola_nodos.push(nodo_actual->derecho);
        }
    }
    return ancho_mayor;
}

// ---------- Reflejo ----------
void ArbolBinarioBusqueda::reflejar_recursivo(Nodo* nodo) {
    if (nodo == nullptr) return;
    std::swap(nodo->izquierdo, nodo->derecho);
    reflejar_recursivo(nodo->izquierdo);
    reflejar_recursivo(nodo->derecho);
}
void ArbolBinarioBusqueda::reflejar() { reflejar_recursivo(raiz_); }

bool ArbolBinarioBusqueda::vacio() const { return raiz_ == nullptr; }
