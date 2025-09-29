#include <iostream>
using namespace std;

// Definición de un nodo
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// Insertar al inicio
void insertarInicio(Nodo*& head, int valor) {
    Nodo* nuevo = crearNodo(valor);
    nuevo->siguiente = head;
    head = nuevo;
}

// Insertar al final
void insertarFinal(Nodo*& head, int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (head == nullptr) {
        head = nuevo;
        return;
    }
    Nodo* aux = head;
    while (aux->siguiente != nullptr) {
        aux = aux->siguiente;
    }
    aux->siguiente = nuevo;
}

// Insertar en posición específica (0 = inicio)
void insertarPos(Nodo*& head, int pos, int valor) {
    if (pos == 0) {
        insertarInicio(head, valor);
        return;
    }

    Nodo* aux = head;
    for (int i = 0; i < pos - 1 && aux != nullptr; i++) {
        aux = aux->siguiente;
    }

    if (aux == nullptr) {
        cout << "Posición inválida" << endl;
        return;
    }

    Nodo* nuevo = crearNodo(valor);
    nuevo->siguiente = aux->siguiente;
    aux->siguiente = nuevo;
}

// Función para mostrar la lista
void mostrarLista(Nodo* head) {
    Nodo* aux = head;
    while (aux != nullptr) {
        cout << aux->dato << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL" << endl;
}

// Programa principal
int main() {
    Nodo* head = nullptr;  // Lista vacía

    insertarInicio(head, 10);
    insertarInicio(head, 5);
    insertarFinal(head, 20);
    insertarPos(head, 1, 15); // Inserta 15 en la posición 1

    cout << "Lista enlazada: ";
    mostrarLista(head);

    return 0;
}