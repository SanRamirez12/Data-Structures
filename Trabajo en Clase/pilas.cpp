#include <iostream>     // Para std::cout / std::cerr
#include <stdexcept>    // Para std::runtime_error
#include <string>       // Para std::string en print()

// ====================== INTERFAZ (CONTRATO) ======================
// Definimos una "interfaz" para una pila de enteros usando una clase abstracta.
// Cualquier implementación concreta debe proveer estos métodos.
struct IPila {
    virtual bool llena() const = 0;                       // ¿Está llena?
    virtual bool vacia() const = 0;                       // ¿Está vacía?
    virtual void push(int elem) = 0;                      // Mete un elemento arriba
    virtual int  pop() = 0;                               // Saca y retorna el de arriba
    virtual void print(const std::string& etiqueta = "") const = 0; // Muestra contenido
    virtual ~IPila() = default;                           // Destructor virtual
};

// ====================== IMPLEMENTACIÓN CON ARREGLO ======================
// Pila concreta basada en un arreglo de tamaño fijo (CAP).
class Pila : public IPila {
    static constexpr int CAP = 10; // Capacidad máxima de la pila (índices 0..9)
    int datos[CAP];                // Arreglo que almacena los elementos
    int tope;                      // Índice del elemento en el tope; -1 => vacía

public:
    // Constructor: inicia la pila vacía
    Pila() : tope(-1) {}

    // La pila está llena si el tope está en la última posición válida
    bool llena() const override { return tope == CAP - 1; }

    // La pila está vacía si no hay ningún elemento (tope == -1)
    bool vacia() const override { return tope == -1; }

    // Inserta un elemento en el tope.
    // Además imprime el estado de la pila después del push.
    void push(int elem) override {
        if (llena()) throw std::runtime_error("Pila llena");
        datos[++tope] = elem;  // Primero incrementa el tope y luego guarda el valor
        std::cout << "push(" << elem << ")  ->  ";
        print();               // Muestra la pila actualizada
    }

    // Extrae y retorna el elemento del tope.
    int pop() override {
        if (vacia()) throw std::runtime_error("Pila vacia");
        return datos[tope--];  // Devuelve el de arriba y luego decrementa el tope
    }

    // Imprime la pila en formato: [elementos]  (abajo … arriba)
    // Mostramos desde el fondo (índice 0) hasta el tope.
    void print(const std::string& etiqueta = "") const override {
        if (!etiqueta.empty()) std::cout << etiqueta;
        std::cout << "[";
        if (!vacia()) {
            for (int i = 0; i <= tope; ++i) {
                std::cout << datos[i];
                if (i < tope) std::cout << " ";
            }
        }
        std::cout << "]  (abajo … arriba)\n";
    }
};

// ====================== FUNCIÓN QUE INVIERTE UNA PILA ======================
// Toma una pila por valor (copia local) y devuelve una nueva pila con el orden invertido.
// Estrategia: ir haciendo pop de 'p' y push en 'r' (dos veces LIFO = reverse).
Pila DaVueltaPila(Pila p) {
    Pila r;                       // Pila resultado (inicialmente vacía)
    while (!p.vacia()) {          // Mientras queden elementos en la original
        r.push(p.pop());          // Saca de 'p' y mete en 'r' (se imprime en push)
    }
    return r;                     // Devuelve la pila invertida
}

// ====================== DEMOSTRACIÓN ======================
int main() {
    try {
        Pila p;                   // Creamos una pila vacía

        // Insertamos 3, 3, 5 (cada push imprime el estado)
        p.push(3);
        p.push(3);
        p.push(5);

        // Visualizamos cómo quedó la pila original
        p.print("Pila original: ");   // Esperado: [3 3 5] (5 es el tope)

        // Invertimos la pila
        Pila q = DaVueltaPila(p);     // q será [5 3 3]
        q.print("Pila invertida: ");  // Imprime el resultado

    } catch (const std::exception& ex) {
        // Si intentas hacer pop en vacía o push en llena, terminarás aquí
        std::cerr << "ERROR: " << ex.what() << "\n";
    }
    return 0; // Fin correcto del programa
}
