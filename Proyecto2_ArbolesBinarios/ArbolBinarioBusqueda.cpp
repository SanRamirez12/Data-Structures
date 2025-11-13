#include "ArbolBinarioBusqueda.h"
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// ---------- Nodo ----------

/**
 * @brief Constructor del nodo interno del árbol.
 * @param estudiante Estudiante a almacenar en el nodo.
 * @details
 * Calcula y asigna la clave de promedio en centésimas a partir del
 * promedio del estudiante, toma el ID como clave secundaria y
 * establece los punteros izquierdo y derecho en nullptr.
 */
ArbolBinarioBusqueda::Nodo::Nodo(const Estudiante& estudiante)
    : clave_promedio_cent(convertir_promedio_a_clave(estudiante.promedio())),
    clave_id(estudiante.id()),
    dato(estudiante),
    izquierdo(nullptr),
    derecho(nullptr) {
}

// ---------- Constructor / Destructor ----------

/**
 * @brief Constructor por defecto del árbol binario de búsqueda.
 * @details
 * Inicializa la raíz en nullptr, indicando que el árbol comienza vacío.
 */
ArbolBinarioBusqueda::ArbolBinarioBusqueda() : raiz_(nullptr) {}

/**
 * @brief Destructor del árbol binario de búsqueda.
 * @details
 * Libera todos los nodos del árbol utilizando un recorrido postorden,
 * para evitar fugas de memoria, y luego pone la raíz en nullptr.
 */
ArbolBinarioBusqueda::~ArbolBinarioBusqueda() {
    liberar_postorden(raiz_);
    raiz_ = nullptr;
}

// ---------- Utilidades privadas ----------

/**
 * @brief Compara dos claves (promedio en centésimas, id).
 * @param g1 Promedio (en centésimas) del primer elemento.
 * @param id1 ID del primer elemento.
 * @param g2 Promedio (en centésimas) del segundo elemento.
 * @param id2 ID del segundo elemento.
 * @return
 * - -1 si (g1, id1) es menor que (g2, id2)
 * -  1 si (g1, id1) es mayor que (g2, id2)
 * -  0 si ambas claves son equivalentes.
 * @details
 * La comparación se realiza primero por promedio; si los promedios
 * son iguales, se desempata usando el ID.
 */
int ArbolBinarioBusqueda::comparar_claves(int g1, int id1, int g2, int id2) {
    if (g1 < g2) return -1;
    if (g1 > g2) return 1;
    if (id1 < id2) return -1;
    if (id1 > id2) return 1;
    return 0;
}

/**
 * @brief Libera recursivamente todos los nodos de un subárbol en postorden.
 * @param nodo Nodo raíz del subárbol a liberar.
 * @details
 * Primero se libera el subárbol izquierdo, luego el derecho y por último
 * el nodo actual. Esta función se utiliza en el destructor del árbol.
 */
void ArbolBinarioBusqueda::liberar_postorden(Nodo* nodo) {
    if (nodo == nullptr) return;
    liberar_postorden(nodo->izquierdo);
    liberar_postorden(nodo->derecho);
    delete nodo;
}

// ---------- Inserción / Búsqueda ----------

/**
 * @brief Inserta un estudiante de forma recursiva en el subárbol dado.
 * @param nodo Raíz actual del subárbol donde se desea insertar.
 * @param estudiante Estudiante a insertar o actualizar.
 * @return Nueva raíz del subárbol tras la operación de inserción.
 * @details
 * Si la posición adecuada está vacía (nodo == nullptr), se crea un nuevo
 * nodo. Si la clave ya existe, se actualiza el dato del nodo con el nuevo
 * estudiante.
 */
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

/**
 * @brief Inserta un estudiante en el árbol.
 * @param estudiante Estudiante a insertar.
 * @details
 * Llama internamente a la versión recursiva de inserción partiendo desde
 * la raíz y actualiza la raíz en caso de que el árbol estuviera vacío.
 */
void ArbolBinarioBusqueda::insertar(const Estudiante& estudiante) {
    raiz_ = insertar_recursivo(raiz_, estudiante);
}

/**
 * @brief Busca un nodo por promedio (en centésimas) de forma recursiva.
 * @param nodo Raíz del subárbol donde se realiza la búsqueda.
 * @param clave_promedio_cent Promedio en centésimas a buscar.
 * @return Puntero al nodo encontrado o nullptr si no se encuentra.
 * @details
 * Aprovecha la propiedad de orden del árbol, y se mueve a izquierda o derecha
 * dependiendo de si la clave buscada es menor o mayor que la del nodo actual.
 */
ArbolBinarioBusqueda::Nodo* ArbolBinarioBusqueda::buscar_por_promedio_recursivo(Nodo* nodo, int clave_promedio_cent) {
    if (nodo == nullptr) return nullptr;
    if (clave_promedio_cent < nodo->clave_promedio_cent) return buscar_por_promedio_recursivo(nodo->izquierdo, clave_promedio_cent);
    if (clave_promedio_cent > nodo->clave_promedio_cent) return buscar_por_promedio_recursivo(nodo->derecho, clave_promedio_cent);
    return nodo; // primer match del promedio
}

/**
 * @brief Busca un estudiante por su promedio (coincidencia exacta).
 * @param promedio Promedio académico en escala 0.0 - 100.0.
 * @return Puntero constante al estudiante si se encuentra, nullptr en caso contrario.
 * @details
 * Convierte el promedio a su clave en centésimas y realiza una búsqueda
 * recursiva en el árbol. Devuelve el primer nodo que coincida con ese promedio.
 */
const Estudiante* ArbolBinarioBusqueda::buscar_por_promedio(double promedio) {
    const int clave_busqueda = convertir_promedio_a_clave(promedio);
    Nodo* nodo_encontrado = buscar_por_promedio_recursivo(raiz_, clave_busqueda);
    return nodo_encontrado ? &nodo_encontrado->dato : nullptr;
}

/**
 * @brief Busca un nodo por ID de manera recursiva.
 * @param nodo Raíz del subárbol donde se realizará la búsqueda.
 * @param id ID del estudiante a buscar.
 * @return Puntero al nodo encontrado o nullptr si no se encuentra.
 * @warning El árbol no está ordenado por ID, por lo que esta función
 *          puede llegar a recorrer todos los nodos del árbol.
 */
ArbolBinarioBusqueda::Nodo* ArbolBinarioBusqueda::buscar_por_id_recursivo(Nodo* nodo, int id) {
    if (nodo == nullptr) return nullptr;
    if (nodo->dato.id() == id) return nodo;

    Nodo* resultado_izquierdo = buscar_por_id_recursivo(nodo->izquierdo, id);
    if (resultado_izquierdo != nullptr) return resultado_izquierdo;

    return buscar_por_id_recursivo(nodo->derecho, id);
}

/**
 * @brief Busca un estudiante por su ID.
 * @param id Identificador del estudiante a buscar.
 * @return Puntero constante al estudiante si se encuentra, nullptr en caso contrario.
 */
const Estudiante* ArbolBinarioBusqueda::buscar_por_id(int id) {
    Nodo* nodo_encontrado = buscar_por_id_recursivo(raiz_, id);
    return nodo_encontrado ? &nodo_encontrado->dato : nullptr;
}

// ---------- Recorridos recursivos (públicos) ----------

/**
 * @brief Recorre el árbol en preorden de forma recursiva (interfaz pública).
 * @param visitar Función callback que se aplica a cada estudiante visitado.
 * @details
 * En preorden se visita primero el nodo actual, luego el subárbol izquierdo
 * y al final el subárbol derecho.
 */
void ArbolBinarioBusqueda::preorden_rec(const function<void(const Estudiante&)>& visitar) const {
    preorden_recursivo(raiz_, visitar);
}

/**
 * @brief Recorre el árbol en inorden de forma recursiva (interfaz pública).
 * @param visitar Función callback que se aplica a cada estudiante visitado.
 * @details
 * En inorden se visita primero el subárbol izquierdo, luego el nodo actual
 * y al final el subárbol derecho, obteniendo los datos en orden ascendente
 * según la clave.
 */
void ArbolBinarioBusqueda::inorden_rec(const function<void(const Estudiante&)>& visitar) const {
    inorden_recursivo(raiz_, visitar);
}

/**
 * @brief Recorre el árbol en postorden de forma recursiva (interfaz pública).
 * @param visitar Función callback que se aplica a cada estudiante visitado.
 * @details
 * En postorden se visita primero el subárbol izquierdo, luego el derecho
 * y por último el nodo actual.
 */
void ArbolBinarioBusqueda::postorden_rec(const function<void(const Estudiante&)>& visitar) const {
    postorden_recursivo(raiz_, visitar);
}

// ---------- Recorridos recursivos (privados) ----------

/**
 * @brief Implementación recursiva del recorrido en preorden.
 * @param nodo Nodo actual del subárbol.
 * @param visitar Función callback para procesar el dato del nodo.
 */
void ArbolBinarioBusqueda::preorden_recursivo(Nodo* nodo, const function<void(const Estudiante&)>& visitar) {
    if (nodo == nullptr) return;
    visitar(nodo->dato);
    preorden_recursivo(nodo->izquierdo, visitar);
    preorden_recursivo(nodo->derecho, visitar);
}

/**
 * @brief Implementación recursiva del recorrido en inorden.
 * @param nodo Nodo actual del subárbol.
 * @param visitar Función callback para procesar el dato del nodo.
 */
void ArbolBinarioBusqueda::inorden_recursivo(Nodo* nodo, const function<void(const Estudiante&)>& visitar) {
    if (nodo == nullptr) return;
    inorden_recursivo(nodo->izquierdo, visitar);
    visitar(nodo->dato);
    inorden_recursivo(nodo->derecho, visitar);
}

/**
 * @brief Implementación recursiva del recorrido en postorden.
 * @param nodo Nodo actual del subárbol.
 * @param visitar Función callback para procesar el dato del nodo.
 */
void ArbolBinarioBusqueda::postorden_recursivo(Nodo* nodo, const function<void(const Estudiante&)>& visitar) {
    if (nodo == nullptr) return;
    postorden_recursivo(nodo->izquierdo, visitar);
    postorden_recursivo(nodo->derecho, visitar);
    visitar(nodo->dato);
}

// ---------- Recorridos iterativos ----------

/**
 * @brief Recorre el árbol en preorden de forma iterativa.
 * @param visitar Función callback para procesar cada estudiante.
 * @details
 * Utiliza una pila explícita en lugar de recursión. Se apilan primero
 * los hijos derechos y luego los izquierdos, para respetar el orden
 * de visita (nodo, izquierdo, derecho).
 */
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

/**
 * @brief Recorre el árbol en inorden de forma iterativa.
 * @param visitar Función callback para procesar cada estudiante.
 * @details
 * Emplea una pila para simular el comportamiento de la recursión, bajando
 * por la izquierda hasta el fondo y luego retrocediendo por la derecha.
 */
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

/**
 * @brief Recorre el árbol en postorden de forma iterativa.
 * @param visitar Función callback para procesar cada estudiante.
 * @details
 * Utiliza dos pilas: una para el recorrido inicial y otra para invertir
 * el orden de visita, obteniendo finalmente el orden postorden.
 */
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

/**
 * @brief Recorre el árbol por niveles (BFS).
 * @param visitar Función callback que recibe el estudiante y su nivel.
 * @details
 * Emplea una cola de pares (nodo, nivel). El nivel de la raíz comienza
 * en 0, y cada vez que se desciende a un hijo se incrementa en 1.
 */
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

/**
 * @brief Calcula la altura de un subárbol de forma recursiva.
 * @param nodo Nodo raíz del subárbol.
 * @return Altura del subárbol.
 * @details
 * Se define que un árbol vacío tiene altura -1 y un árbol con un solo
 * nodo (hoja) tiene altura 0. La altura es 1 + el máximo entre las
 * alturas de los subárboles izquierdo y derecho.
 */
int ArbolBinarioBusqueda::altura_recursiva(Nodo* nodo) {
    if (nodo == nullptr) return -1; // árbol vacío = -1; un nodo = 0
    int altura_izquierda = altura_recursiva(nodo->izquierdo);
    int altura_derecha = altura_recursiva(nodo->derecho);
    return 1 + std::max(altura_izquierda, altura_derecha);
}

/**
 * @brief Obtiene la altura del árbol completo.
 * @return Altura del árbol, o -1 si está vacío.
 */
int ArbolBinarioBusqueda::altura() const { return altura_recursiva(raiz_); }

/**
 * @brief Cuenta el número de nodos en un subárbol de forma recursiva.
 * @param nodo Nodo raíz del subárbol.
 * @return Cantidad total de nodos en ese subárbol.
 */
int ArbolBinarioBusqueda::contar_nodos_recursivo(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contar_nodos_recursivo(nodo->izquierdo) + contar_nodos_recursivo(nodo->derecho);
}

/**
 * @brief Cuenta el número total de nodos del árbol.
 * @return Cantidad de nodos almacenados en el árbol.
 */
int ArbolBinarioBusqueda::contar_nodos() const { return contar_nodos_recursivo(raiz_); }

/**
 * @brief Cuenta el número de hojas de un subárbol.
 * @param nodo Nodo raíz del subárbol.
 * @return Cantidad de nodos hoja (sin hijos) en ese subárbol.
 */
int ArbolBinarioBusqueda::contar_hojas_recursivo(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
    return contar_hojas_recursivo(nodo->izquierdo) + contar_hojas_recursivo(nodo->derecho);
}

/**
 * @brief Cuenta el número de hojas del árbol.
 * @return Cantidad de nodos hoja del árbol completo.
 */
int ArbolBinarioBusqueda::contar_hojas() const { return contar_hojas_recursivo(raiz_); }

/**
 * @brief Cuenta el número de nodos internos del árbol.
 * @return Cantidad de nodos con al menos un hijo.
 * @details
 * Se obtiene restando el número de hojas al número total de nodos.
 */
int ArbolBinarioBusqueda::contar_internos() const {
    return contar_nodos() - contar_hojas();
}

/**
 * @brief Calcula el ancho máximo del árbol.
 * @return Número máximo de nodos encontrados en cualquier nivel.
 * @details
 * Recorre el árbol por niveles y, para cada nivel, cuenta cuántos
 * nodos hay, quedándose con el máximo observado.
 */
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

/**
 * @brief Genera el reflejo de un subárbol de forma recursiva.
 * @param nodo Nodo raíz del subárbol a reflejar.
 * @details
 * Intercambia los punteros a los hijos izquierdo y derecho de cada nodo,
 * aplicando el mismo proceso recursivamente a ambos subárboles.
 */
void ArbolBinarioBusqueda::reflejar_recursivo(Nodo* nodo) {
    if (nodo == nullptr) return;
    std::swap(nodo->izquierdo, nodo->derecho);
    reflejar_recursivo(nodo->izquierdo);
    reflejar_recursivo(nodo->derecho);
}

/**
 * @brief Genera el reflejo del árbol completo.
 * @details
 * Llama a la función recursiva de reflejo comenzando desde la raíz.
 */
void ArbolBinarioBusqueda::reflejar() { reflejar_recursivo(raiz_); }

/**
 * @brief Indica si el árbol está vacío.
 * @return true si la raíz es nullptr, false en caso contrario.
 */
bool ArbolBinarioBusqueda::vacio() const { return raiz_ == nullptr; }
