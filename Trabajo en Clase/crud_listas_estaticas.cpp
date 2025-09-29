
#include <iostream>
using namespace std;

#define MAX 100  // Tamaño máximo de la lista

// Algoritmo Insertar
void Insertar(int Lista[], int &N, int Pos, int Elem) {
    if (N == MAX) {
        cout << "Lista llena, no se puede insertar" << endl;
    }
    else if (Pos < 0 || Pos > N) {
        cout << "Posición inválida" << endl;
    }
    else {
        // Desplazar a la derecha
        for (int i = N - 1; i >= Pos; i--) {
            Lista[i + 1] = Lista[i];
        }
        // Insertar elemento
        Lista[Pos] = Elem;
        N = N + 1;
    }
}

// Mostrar lista
void Mostrar(int Lista[], int N) {
    cout << "Lista: ";
    for (int i = 0; i < N; i++) {
        cout << Lista[i] << " ";
    }
    cout << endl;
}

int main() {
    int Lista[MAX];
    int N = 0; // cantidad actual de elementos

    // Insertar usando el algoritmo
    Insertar(Lista, N, 0, 10); // Insertar 10 en posición 0
    Mostrar(Lista, N);
    Insertar(Lista, N, 1, 20); // Insertar 20 en posición 1
    Mostrar(Lista, N);
    Insertar(Lista, N, 1, 15); // Insertar 15 en posición 1 (entre 10 y 20)
  //  Mostrar(Lista, N);
    //Insertar(Lista, N, 5, 50); // Posición inválida (ejemplo)

    Mostrar(Lista, N);
    Insertar(Lista, N, 1, 50); // Posición inválida (ejemplo)
    Mostrar(Lista, N);
    return 0;
}
