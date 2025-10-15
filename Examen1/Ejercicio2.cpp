#include <iostream>                 //E/S por consola
#include <string>                   //std::string y getline
#include <vector>                   //Para reunir letras de max/min al final

/* -----------------------------
 Nodo para letra y frecuencia
 -----------------------------*/
struct NodoLetra {
    char letra;                     //Letra (minúscula, sin acento)
    int  frecuencia;                //Cantidad de apariciones
    NodoLetra* siguiente;           //Enlace al siguiente nodo

    explicit NodoLetra(char c)      //Constructor que inicia en 1 ocurrencia
        : letra(c), frecuencia(1), siguiente(nullptr) {}
};

/* -------------------------------------------------------
 Lista simplemente enlazada ordenada por 'letra' (a..z)
 -------------------------------------------------------*/
class ListaFrecuencias {
public:
    ListaFrecuencias() : cabeza(nullptr) {}       //Lista vacía

    ~ListaFrecuencias() { limpiar(); }            //Libera memoria al destruir

    //Inserta o incrementa manteniendo orden alfabético O(L)
    void insertar_o_incrementar(char c) {
        //Si la lista está vacía, el nuevo nodo es la cabeza.
        if (!cabeza) { cabeza = new NodoLetra(c); return; }

        //Caso especial: la letra va antes de la cabeza (o es la misma).
        if (c <= cabeza->letra) {
            if (c == cabeza->letra) {            //Misma letra: contar
                cabeza->frecuencia++;
            } else {                              //Menor letra: insertar al inicio
                NodoLetra* nuevo = new NodoLetra(c);
                nuevo->siguiente = cabeza;
                cabeza = nuevo;
            }
            return;
        }

        //Recorremos buscando posición: 'anterior' y 'actual'
        NodoLetra* anterior = cabeza;
        NodoLetra* actual   = cabeza->siguiente;

        while (actual && actual->letra < c) {     //Avanza mientras actual < c
            anterior = actual;
            actual   = actual->siguiente;
        }

        if (actual && actual->letra == c) {       //Encontramos la letra: sumar
            actual->frecuencia++;
        } else {                                   //Insertar nuevo nodo entre anterior y actual
            NodoLetra* nuevo = new NodoLetra(c);
            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
        }
    }

    //Recorre e imprime la lista con el formato [a:2] -> [c:1] -> ...
    void imprimir() const {
        const NodoLetra* p = cabeza;
        std::cout << "[";
        while (p) {
            std::cout << p->letra << ":" << p->frecuencia;
            if (p->siguiente) std::cout << "] -> [";
            p = p->siguiente;
        }
        std::cout << "]\n";
    }

    //Obtiene (por referencia) mayor y menor frecuencia y las letras que las tienen
    void obtener_mayor_y_menor(int& mayor, int& menor,
                                std::vector<char>& letras_mayor,
                                std::vector<char>& letras_menor) const
    {
        //Si no hay datos, dejamos mayor/menor en 0 y vacías las listas
        if (!cabeza) {mayor = menor = 0; letras_mayor.clear(); letras_menor.clear(); return; }

        //Inicializamos mayor/menor con la cabeza
        mayor = menor = cabeza->frecuencia;
        letras_mayor = { cabeza->letra };
        letras_menor = { cabeza->letra };

        //Recorremos el resto ajustando max/min y colecciones
        const NodoLetra* p = cabeza->siguiente;
        while (p) {
            if (p->frecuencia > mayor) {              //Nuevo máximo
                mayor = p->frecuencia;
                letras_mayor.clear();
                letras_mayor.push_back(p->letra);
            } else if (p->frecuencia == mayor) {      //Empata con el máximo
                letras_mayor.push_back(p->letra);
            }

            if (p->frecuencia < menor) {              //Nuevo mínimo
                menor = p->frecuencia;
                letras_menor.clear();
                letras_menor.push_back(p->letra);
            } else if (p->frecuencia == menor) {      //Empata con el mínimo
                letras_menor.push_back(p->letra);
            }
            p = p->siguiente;                          //Avanzar
        }
    }

    //Libera todos los nodos
    void limpiar() {
        NodoLetra* p = cabeza;
        while (p) {
            NodoLetra* q = p->siguiente;
            delete p;
            p = q;
        }
        cabeza = nullptr;
    }

private:
    NodoLetra* cabeza;                                 // Inicio de la lista

    //Copia/assign deshabilitados para evitar dobles delete (propiedad de nodos)
    ListaFrecuencias(const ListaFrecuencias&) = delete;
    ListaFrecuencias& operator=(const ListaFrecuencias&) = delete;
};

/* -------------------------------------------------------
 Utilidades de normalización de caracteres
-------------------------------------------------------*/

//Convierte a minúscula simple (solo para ASCII básico)
char a_minuscula(char c) {
    if (c >= 'A' && c <= 'Z') return char(c - 'A' + 'a');
    return c;
}

//Mapea vocales acentuadas/diéresis y ñ a su base sin diacrítico.
//Si no es letra a..z tras normalizar, devuelve 0 para "ignorar".
char normalizar_letra_es(char c) {
    c = a_minuscula(c);                     //Primero, minúscula

    //Tabla simple de mapeo manual
    unsigned char uc = static_cast<unsigned char>(c);
    switch (uc){
        case '\xE1': case 'á': return 'a';  //Dependiendo del compilador, 'á' puede equivaler a 0xE1
        case '\xE9': case 'é': return 'e';
        case '\xED': case 'í': return 'i';
        case '\xF3': case 'ó': return 'o';
        case '\xFA': case 'ú': return 'u';
        case '\xFC': case 'ü': return 'u';
        case '\xF1': case 'ñ': return 'n';
        default: break;
    }

    //Si es letra latina básica, se acepta tal cual
    if (c >= 'a' && c <= 'z') return c;

    //Todo lo demás se ignora
    return 0;
}

/* -------------------------------------------------------
 Programa principal
 -------------------------------------------------------*/
int main() {
    std::string texto;                                  //Cadena de entrada

    //Pedimos una línea (permite espacios)
    std::cout << "Ingrese el texto: ";
    std::getline(std::cin, texto);

    ListaFrecuencias lista;                             //Lista enlazada de frecuencias

    //Recorremos cada carácter del texto
    for (char ch : texto) {
        char norm = normalizar_letra_es(ch);            //Normaliza (acentos → base, minúscula)
        if (norm == 0) continue;                        //Ignora si no es letra válida
        lista.insertar_o_incrementar(norm);             //Inserta/incrementa manteniendo orden
    }

    //Imprimir la lista resultante
    std::cout << "\nLista (letra:frecuencia) ordenada:\n  ";
    lista.imprimir();

    //Calcular mayor y menor frecuencia + letras asociadas
    int mayor = 0, menor = 0;
    std::vector<char> letras_mayor, letras_menor;
    lista.obtener_mayor_y_menor(mayor, menor, letras_mayor, letras_menor);

    //Reporte de mayor frecuencia
    std::cout << "\nMayor Frecuencia: " << mayor << " (letras: ";
    for (size_t i = 0; i < letras_mayor.size(); ++i) {
        std::cout << letras_mayor[i];
        if (i + 1 < letras_mayor.size()) std::cout << ", ";
    }
    std::cout << ")\n";

    //Reporte de menor frecuencia
    std::cout << "Menor Frecuencia: " << menor << " (letras: ";
    for (size_t i = 0; i < letras_menor.size(); ++i) {
        std::cout << letras_menor[i];
        if (i + 1 < letras_menor.size()) std::cout << ", ";
    }
    std::cout << ")\n";

    return 0;                                           //Fin del programa
}
