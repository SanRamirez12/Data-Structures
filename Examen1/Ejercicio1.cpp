#include <iostream>          // Incluye la librería estándar para E/S por consola
#include <vector>            // Incluye std::vector para construir listas de prueba

/* -----------------------------
 Definición del nodo básico
-----------------------------*/ 
struct Nodo {
    int dato;  //Valor almacenado en el nodo
    Nodo* siguiente; //Puntero al siguiente nodo de la lista

    explicit Nodo(int v)  //Constructor que recibe el entero a guardar
        : dato(v), siguiente(nullptr) {}  //Inicializa 'dato' y pone 'siguiente' en null
};

/* -------------------------------------------------------
 Lista simplemente enlazada con operaciones de utilidad
-------------------------------------------------------*/
class ListaEnlazada {
public:
    ListaEnlazada() //Constructor por defecto
        : cabeza(nullptr), cola(nullptr), n(0) {}  //Lista vacía: punteros nulos y tamaño 0

    ~ListaEnlazada() { //Destructor
        limpiar();     //Libera toda la memoria de los nodos que aún posea la lista
    }

    //Inserta al final en O(1)
    void agregar_al_final(int v) { //Agrega un número al final de la lista
        anexar_nodo(new Nodo(v));  //Crea un nodo en heap y lo anexa
    }

    //Crea una lista a partir de un vector de enteros (ayuda para pruebas)
    static ListaEnlazada desde_vector(const std::vector<int>& valores) {
        ListaEnlazada L;               //Crea una lista vacía
        for (int v : valores)          //Recorre cada entero del vector
            L.agregar_al_final(v);     //Lo agrega al final
        return L;                      //Devuelve la lista construida (NRVO/move)
    }

    //Recorre la lista y EXTRAE los múltiplos de 10 a otra lista (mueve nodos, no copia)
    ListaEnlazada extraer_multiplos_de_10() {
        ListaEnlazada resultado;       //Lista destino con los múltiplos de 10

        Nodo* anterior = nullptr;      //Puntero al nodo previo al actual (para poder "desenganchar")
        Nodo* actual   = cabeza;       //Empieza a recorrer desde la cabeza

        while (actual) {                       //Mientras queden nodos por revisar
            Nodo* siguiente = actual->siguiente;  //Guarda el siguiente antes de modificar enlaces

            if (actual->dato % 10 == 0) {      //¿El valor es múltiplo de 10?
                //Quitar 'actual' de esta lista (la original)
                if (anterior)                   //Si no estamos en la cabeza, salta el nodo actual
                    anterior->siguiente = siguiente; 
                else                            //Si estamos en la cabeza, la nueva cabeza es el siguiente
                    cabeza = siguiente;          

                if (actual == cola)             // Si quitamos la cola, actualizamos la cola
                    cola = anterior;            

                n--;                             //Disminuye el tamaño de la lista original

                //Anexar el nodo extraído a la lista resultado
                actual->siguiente = nullptr;     //El nodo irá al final, su siguiente debe ser null
                resultado.anexar_nodo(actual);   //Mueve el nodo (transfiere propiedad)
            } else {
                //Si no es múltiplo de 10, solo avanzamos 'anterior'
                anterior = actual;               //El actual pasa a ser el anterior
            }

            actual = siguiente;                  //Avanza al siguiente nodo guardado
        }

        return resultado;                        //Devuelve la lista de múltiplos de 10
    }

    bool vacia() const {          //¿La lista no tiene nodos?
        return cabeza == nullptr; //Verdadero si cabeza es null
    }

    size_t tamano() const {       //Devuelve el número de nodos actuales
        return n;                 //Retorna el contador interno
    }

    void imprimir() const {                     //Muestra la lista con el formato [a -> b -> c]
        const Nodo* p = cabeza;                 //Empieza desde la cabeza (puntero de solo lectura)
        std::cout << "[";                       //Abre corchete
        while (p) {                             //Recorre mientras haya nodo
            std::cout << p->dato;               //Imprime el valor del nodo
            if (p->siguiente) std::cout << " -> "; //Flecha si no es el último
            p = p->siguiente;                   //Avanza al siguiente
        }
        std::cout << "]\n";                     //Cierra corchete y salto de línea
    }

    void limpiar() {                            //Libera todos los nodos de la lista
        Nodo* p = cabeza;                       //Empieza desde la cabeza
        while (p) {                             //Mientras queden nodos
            Nodo* q = p->siguiente;             //Guarda el siguiente
            delete p;                           //Libera el nodo actual
            p = q;                               //Avanza
        }
        cabeza = cola = nullptr;                //Deja la lista en estado vacío
        n = 0;                                  //Tamaño a 0
    }

private:
    Nodo* cabeza;                 //Puntero al primer nodo de la lista
    Nodo* cola;                   //Puntero al último nodo (para insertar en O(1))
    size_t n;                     //Número de nodos de la lista

    //Anexa un nodo EXISTENTE al final (transfiere la propiedad del puntero a la lista)
    void anexar_nodo(Nodo* nodo) {
        if (!nodo) return;                     //Si el puntero viene nulo, no hace nada
        if (!cabeza) {                         //Si la lista está vacía,
            cabeza = cola = nodo;              //cabeza y cola apuntan al nuevo nodo
        } else {                               //Si ya hay elementos,
            cola->siguiente = nodo;            //enlaza el nuevo después de la cola actual
            cola = nodo;                       //actualiza la cola al nuevo nodo
        }
        n++;                                   //Incrementa el tamaño
    }

    //Evitamos copias para no provocar dobles 'delete' (lista posee los nodos)
    ListaEnlazada(const ListaEnlazada&) = delete;            //Sin constructor de copia
    ListaEnlazada& operator=(const ListaEnlazada&) = delete; //Sin asignación por copia

    //Permitimos movimientos para transferir propiedad de forma segura/eficiente
    ListaEnlazada(ListaEnlazada&& otra) noexcept             //Constructor por movimiento
        : cabeza(otra.cabeza), cola(otra.cola), n(otra.n) {  //Toma los punteros y tamaño
        otra.cabeza = otra.cola = nullptr;                   //Deja la otra lista vacía
        otra.n = 0;                                          //y tamaño 0
    }

    ListaEnlazada& operator=(ListaEnlazada&& otra) noexcept { //Asignación por movimiento
        if (this != &otra) {                                  //Evita auto-asignación
            limpiar();                                        //Libera los nodos actuales
            cabeza = otra.cabeza;                             //Toma cabeza
            cola   = otra.cola;                               //Toma cola
            n      = otra.n;                                  //Toma tamaño
            otra.cabeza = otra.cola = nullptr;                //Vacía la otra lista
            otra.n = 0;                                       //Tamaño 0 en la otra
        }
        return *this;                                         //Permite encadenar asignaciones
    }
};

/* -----------------------------
 Programa de prueba
 -----------------------------*/
int main() {
    //Construimos la lista de ejemplo: 15 → 20 → 33 → 40 → 51 → 70 → 84
    ListaEnlazada original = ListaEnlazada::desde_vector({15, 20, 33, 40, 51, 70, 84});

    std::cout << "Lista original: \n";
    original.imprimir();                    //Muestra la lista original

    //Extraemos los múltiplos de 10 (mueve nodos a una nueva lista y los quita de la original)
    ListaEnlazada lista_multiplos = original.extraer_multiplos_de_10();

    std::cout << "Lista Original Modificada: \n";
    original.imprimir();                    //Debe quedar: [15 -> 33 -> 51 -> 84]

    std::cout << "Lista de multiplos de 10: \n";
    lista_multiplos.imprimir();             //Debe quedar: [20 -> 40 -> 70]

    return 0;                               //Fin del programa
}
