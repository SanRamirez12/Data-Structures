#include <iostream>

//Se necesita hacer el crud para las listas doblemente enlazadas

//Clase y funcion Nodo:
struct Nodo { //definimos la estructura del nodo
    int dato;
    Nodo* siguiente;  //flecha al siguiente nodo
    Nodo* anterior;   //flecha al nodo anterior
};
/*
siguiente: una flecha (puntero) al nodo de la derecha.
anterior: una flecha (puntero) al nodo de la izquierda.
Cuando una flecha no apunta a nadie, vale "nullptr" o puntero nulo
->: se accede a los campos de un puntero
*/
Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo;   //reserva memoria para un Nodo
    nuevo->dato = valor;      //guarda el valor
    nuevo->siguiente = nullptr;
    nuevo->anterior  = nullptr;
    return nuevo;             //devuelve la dirección del nodo
}


//Algunas utilidades para metodos relacionados con la clase nodo:
//recorre con cur = cur->siguiente
void imprimirAdelante(Nodo* head) {
    std::cout << "[";
    for (Nodo* cur = head; cur; cur = cur->siguiente) {
        std::cout << cur->dato;
        if (cur->siguiente) std::cout << " <-> ";
    }
    std::cout << "]\n";
}

//recorra al revés con cur = cur->anterior
void imprimirAtrasDesde(Nodo* tail) {
    std::cout << "[";
    for (Nodo* cur = tail; cur; cur = cur->anterior) {
        std::cout << cur->dato;
        if (cur->anterior) std::cout << " <-> ";
    }
    std::cout << "]\n";
}

//va hasta el último para poder que imprimirAtras(tail) recorra al revés con cur = cur->anterior
Nodo* obtenerCola(Nodo* head) {
    if (!head) return nullptr;
    while (head->siguiente) head = head->siguiente;
    return head;
}

//Siempre que se use new, luego libera con delete → LiberarDesdeInicio. 
void liberarDesdeInicio(Nodo* head) {
    while (head) {
        Nodo* sig = head->siguiente;
        delete head;
        head = sig;
    }
}

//Metodo para insertar al inicio:
Nodo* insertarInicio(Nodo* head, int elem) {
    Nodo* nuevo = crearNodo(elem);
    nuevo->siguiente = head;     //Apunta al viejo primero
    if (head) head->anterior = nuevo;
    return nuevo;                //'nuevo' ahora es la cabeza
}

//Metodo para insertar al final:
/*
Si la lista está vacía, el nuevo nodo pasa a ser la cabeza.
Si no, recorre hasta la cola y lo coloca al final.
*/
Nodo* insertarFinal(Nodo* head, int elem) {
    Nodo* nuevo = crearNodo(elem);
    if (!head) return nuevo; //Lista vacía

    Nodo* cola = head;
    while (cola->siguiente) cola = cola->siguiente; //Ir a la cola
    cola->siguiente = nuevo;
    nuevo->anterior = cola;
    return head;            //La cabeza no cambia
}

//Metodo para insertar en cualquier posicion:
/* Posiciones 0..n. Reglas fáciles:
 pos <= 0  => al inicio
 pos >= n  => al final
 en medio  => antes del nodo que actualmente está en 'pos'
*/ 
Nodo* insertarEnPos(Nodo* head, int pos, int elem) {
    if (pos <= 0 || !head) {
        return insertarInicio(head, elem);
    }

    //Avanzar hasta 'pos' pero sin salirnos; guardamos último visitado
    Nodo* cur = head;
    int i = 0;
    while (i < pos && cur->siguiente) {
        cur = cur->siguiente;
        ++i;
    }

    if (i < pos) {
        //Llegamos a la cola y todavía no alcanzamos pos => insertar al final
        Nodo* nuevo = crearNodo(elem);
        cur->siguiente = nuevo;
        nuevo->anterior = cur;
        return head;
    } else {
        //Estamos en el nodo que está en índice 'i' (i == pos).
        //Insertar ANTES de 'cur'.
        Nodo* nuevo = crearNodo(elem);
        nuevo->anterior = cur->anterior;
        nuevo->siguiente = cur;

        if (cur->anterior) cur->anterior->siguiente = nuevo;
        cur->anterior = nuevo;

        //Si 'cur' era la cabeza, ahora la cabeza es 'nuevo'
        if (cur == head) head = nuevo;
        return head;
    }
}


//Metodo de busqueda de un dato de la lista:
//Devuelve el índice (0..n-1) o -1 si no está.
int buscar(Nodo* head, int valor) {
    int idx = 0;
    for (Nodo* cur = head; cur; cur = cur->siguiente, ++idx) {
        if (cur->dato == valor) return idx;
    }
    return -1;
}

//Metodo de eliminar un dato de la lista:
//Actualiza y devuelve la cabeza (podría cambiar si borramos el primero).
Nodo* eliminarValor(Nodo* head, int valor) {
    Nodo* cur = head;
    while (cur && cur->dato != valor) cur = cur->siguiente;
    if (!cur) return head; //no encontrado

    //Reconectar vecinos
    if (cur->anterior) cur->anterior->siguiente = cur->siguiente;
    else               head = cur->siguiente; //cur era cabeza

    if (cur->siguiente) cur->siguiente->anterior = cur->anterior;

    delete cur;
    return head;
}

//main para los ejemplos
int main() {
    Nodo* head = nullptr;

    // Insertar al inicio (base)
    head = insertarInicio(head, 20); // [20]
    head = insertarInicio(head, 10); // [10 <-> 20]
    std::cout << "Tras InsertarInicio x2: "; imprimirAdelante(head);

    // 1) Insertar al final
    head = insertarFinal(head, 30);  // [10 <-> 20 <-> 30]
    head = insertarFinal(head, 40);  // [10 <-> 20 <-> 30 <-> 40]
    std::cout << "Tras InsertarFinal x2: "; imprimirAdelante(head);

    // 2) Insertar en posicion
    head = insertarEnPos(head, 0, 5);          // al inicio: [5,10,20,30,40]
    head = insertarEnPos(head, 3, 25);         // antes de índice 3: [5,10,20,25,30,40]
    head = insertarEnPos(head, 999, 50);       // mayor a n => al final: [...,50]
    std::cout << "Tras InsertarEnPos(0,3,999): "; imprimirAdelante(head);

    // 3) Buscar
    std::cout << "Buscar 25 -> idx=" << buscar(head, 25) << "\n"; //deberia devolver 3 por ser la posicion donde se inserto
    std::cout << "Buscar 99  -> idx=" << buscar(head, 99)  << "\n\n"; //deberia devolver -1 ya que no existe ese dato en la lista

    // 4) Eliminar por valor (primera coincidencia)
    head = eliminarValor(head, 5);   // borra cabeza
    head = eliminarValor(head, 30);  // borra en medio
    head = eliminarValor(head, 50);  // borra cola
    head = eliminarValor(head, 99);  // no existe (sin cambios)
    std::cout << "Tras Eliminar 5,30,50,99: "; imprimirAdelante(head);

    // Mostrar también al revés (para verificar punteros 'anterior')
    std::cout << "Reversa: "; imprimirAtrasDesde(obtenerCola(head));

    // Limpieza
    liberarDesdeInicio(head);
    return 0;
}