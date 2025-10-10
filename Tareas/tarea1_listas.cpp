#include <iostream>  // Librería estándar para entrada/salida (cout, cin)
#include <string>    // Permite el uso de la clase string
using namespace std;

/* ================================================================
   Clase Nodo
   Representa un nodo individual dentro de la lista enlazada.
   Cada nodo contiene un dato (nombre) y un puntero al siguiente nodo.
   ================================================================ */
class Nodo {
public:
    string dato;    // Dato almacenado (nombre)
    Nodo* siguiente; // Puntero que apunta al siguiente nodo en la lista

    // Constructor: inicializa el dato y el puntero
    Nodo(string valor) {
        dato = valor;
        siguiente = nullptr; // Al crearlo, no apunta a ningún otro nodo
    }
};

/* ================================================================
   Clase Lista
   Define una lista enlazada simple que mantiene los datos
   ordenados ascendentemente (alfabéticamente).
   Contiene métodos para insertar, eliminar, recorrer y obtener tamaño.
   ================================================================ */
class Lista {
private:
    Nodo* cabeza;  // Apunta al primer nodo de la lista
    int tam;       // Lleva el conteo del número de elementos en la lista

public:
    /* ------------------------------------------------------------
       Constructor: inicializa una lista vacía
       ------------------------------------------------------------ */
    Lista() {
        cabeza = nullptr; // No hay nodos al inicio
        tam = 0;          // El tamaño inicial es 0
    }

    /* ------------------------------------------------------------
       Método insertar(string nombre)
       Inserta un nuevo nodo de forma ordenada (ascendente).
       La comparación se hace alfabéticamente según el string.
       ------------------------------------------------------------ */
    void insertar(string nombre) {
        Nodo* nuevo = new Nodo(nombre); // Crear un nuevo nodo con el dato recibido

        // Caso 1: si la lista está vacía o el nuevo nombre es menor que el primero
        // entonces el nuevo nodo se coloca al inicio.
        if (cabeza == nullptr || nombre < cabeza->dato) {
            nuevo->siguiente = cabeza; // El siguiente del nuevo apunta al antiguo primer nodo
            cabeza = nuevo;            // Ahora el nuevo nodo es la cabeza
        } 
        else {
            // Caso 2: insertar en una posición intermedia o final
            // Se busca el nodo anterior a la posición donde debe insertarse el nuevo
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr && actual->siguiente->dato < nombre) {
                actual = actual->siguiente;
            }

            // Insertar el nuevo nodo después del nodo encontrado
            nuevo->siguiente = actual->siguiente; // El nuevo apunta al siguiente de actual
            actual->siguiente = nuevo;            // El actual ahora apunta al nuevo nodo
        }

        tam++; // Se incrementa el contador de tamaño
    }

    /* ------------------------------------------------------------
       Método eliminar(string nombre)
       Busca y elimina un nodo con el valor especificado.
       Devuelve true si se eliminó correctamente, o false si no se encontró.
       ------------------------------------------------------------ */
    bool eliminar(string nombre) {
        // Caso 1: lista vacía
        if (cabeza == nullptr)
            return false;

        // Caso 2: el nodo a eliminar es el primero
        if (cabeza->dato == nombre) {
            Nodo* temp = cabeza;          // Guardamos el nodo a eliminar
            cabeza = cabeza->siguiente;   // Movemos la cabeza al siguiente nodo
            delete temp;                  // Liberamos la memoria del nodo eliminado
            tam--;                        // Reducimos el tamaño
            return true;
        }

        // Caso 3: el nodo a eliminar está en el medio o al final
        Nodo* actual = cabeza;
        // Avanzar mientras no se encuentre el nombre y no se llegue al final
        while (actual->siguiente != nullptr && actual->siguiente->dato != nombre) {
            actual = actual->siguiente;
        }

        // Si se encontró el nodo
        if (actual->siguiente != nullptr) {
            Nodo* temp = actual->siguiente;         // Guardamos el nodo que vamos a eliminar
            actual->siguiente = temp->siguiente;    // Saltamos el nodo eliminado
            delete temp;                            // Liberamos la memoria
            tam--;                                  // Reducimos el tamaño
            return true;
        }

        // Si no se encontró el elemento
        return false;
    }

    /* ------------------------------------------------------------
       Método recorrer()
       Devuelve un string con todos los elementos de la lista.
       Cada elemento se separa por un salto de línea ('\n').
       ------------------------------------------------------------ */
    string recorrer() {
        string resultado = "";      // Cadena donde se almacenarán los datos
        Nodo* actual = cabeza;      // Comenzamos desde el inicio de la lista

        // Recorremos la lista hasta llegar al final
        while (actual != nullptr) {
            resultado += actual->dato + "\n"; // Agregar el dato y un salto de línea
            actual = actual->siguiente;       // Avanzar al siguiente nodo
        }

        return resultado; // Devolver la lista completa como string
    }

    /* ------------------------------------------------------------
       Método obtenerTamano()
       Retorna el número actual de elementos en la lista.
       ------------------------------------------------------------ */
    int obtenerTamano() {
        return tam;
    }
};

/* ================================================================
   Función principal (main)
   Prueba la clase Lista con 10 nombres introducidos por el usuario.
   Después de cada inserción:
      - Muestra el contenido de la lista (ordenado ascendentemente)
      - Muestra el tamaño actual.
   Luego prueba la eliminación de un nombre.
   ================================================================ */
int main() {
    Lista lista;       // Crear una instancia de la clase Lista
    string nombre;     // Variable para almacenar los nombres ingresados

    cout << "=== Inserción de 10 nombres en orden ascendente ===" << endl;

    // Leer 10 nombres desde el teclado
    for (int i = 1; i <= 10; i++) {
        cout << "\nIngrese el nombre #" << i << ": ";
        getline(cin, nombre);        // Permite leer nombres con espacios
        lista.insertar(nombre);      // Insertar el nombre en la lista (se ordena automáticamente)

        // Mostrar la lista después de cada inserción
        cout << "\nLista actual:" << endl;
        cout << lista.recorrer();    // Imprimir todos los elementos
        cout << "Tamaño de la lista: " << lista.obtenerTamano() << endl;
    }

    // Prueba del método eliminar
    cout << "\n=== Prueba de eliminación ===" << endl;
    cout << "Ingrese un nombre a eliminar: ";
    getline(cin, nombre);

    // Intentar eliminar el nombre ingresado
    if (lista.eliminar(nombre)) {
        cout << "\n'" << nombre << "' eliminado correctamente." << endl;
    } else {
        cout << "\n'" << nombre << "' no se encontró en la lista." << endl;
    }

    // Mostrar la lista final después de la eliminación
    cout << "\nLista final:" << endl;
    cout << lista.recorrer();
    cout << "Tamaño final: " << lista.obtenerTamano() << endl;

    return 0; // Fin del programa
}