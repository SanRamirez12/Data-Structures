#include <iostream>      // std::cout, std::endl
#include <vector>        // almacenamiento subyacente
#include <stdexcept>     // std::runtime_error

// Cola con tres modos en una sola API:
// 1) FixedFront   : tamaño fijo, frente fijo (dequeue = shift O(n))
// 2) FixedMovable : tamaño fijo, frente movible (no circular) con compactación diferida
// 3) Dynamic      : tamaño variable, buffer circular con crecimiento (duplica capacidad)
class Cola {
public:
    enum class Tipo { FixedFront = 1, FixedMovable = 2, Dynamic = 3 };

private:
    Tipo mode;                 // modo actual
    std::vector<int> buf;      // buffer de datos
    size_t cap;                // capacidad lógica
    size_t n;                  // cantidad de elementos
    size_t f;                  // índice del frente (para 2 y 3)
    size_t r;                  // índice de inserción (para 2)

    // Compacta solo en FixedMovable cuando r llegó al final y hay huecos al inicio
    void compact_if_needed() {
        if (mode != Tipo::FixedMovable) return;
        if (r == cap && f > 0) {
            for (size_t i = 0; i < n; ++i) buf[i] = buf[f + i];
            f = 0;
            r = n;
        }
    }

    // Crece (duplica) la capacidad en Dynamic preservando el orden lógico
    void grow_if_needed() {
        if (mode != Tipo::Dynamic || n < cap) return;
        size_t newCap = cap == 0 ? 1 : cap * 2;
        std::vector<int> nb(newCap);
        for (size_t i = 0; i < n; ++i) nb[i] = buf[(f + i) % cap];
        buf.swap(nb);
        cap = newCap;
        f = 0; // rear se calculará como (f + n) % cap
    }

public:
    explicit Cola(Tipo t, size_t capacity)
        : mode(t), buf(capacity), cap(capacity), n(0), f(0), r(0) {}

    bool   empty()    const { return n == 0; }
    size_t size()     const { return n; }
    size_t capacity() const { return cap; }

    void enqueue(int x) {
        switch (mode) {
            case Tipo::FixedFront: {
                if (n == cap) throw std::runtime_error("Cola llena (FixedFront)");
                buf[n++] = x;
                break;
            }
            case Tipo::FixedMovable: {
                if (n == cap) throw std::runtime_error("Cola llena (FixedMovable)");
                compact_if_needed();
                if (r == cap) throw std::runtime_error("No se pudo compactar (FixedMovable)");
                buf[r++] = x;
                ++n;
                break;
            }
            case Tipo::Dynamic: {
                grow_if_needed();
                size_t rear = (f + n) % cap;
                buf[rear] = x;
                ++n;
                break;
            }
        }
    }

    int front() const {
        if (empty()) throw std::runtime_error("Cola vacia");
        if (mode == Tipo::FixedFront)   return buf[0];
        /* FixedMovable o Dynamic */    return buf[f];
    }

    int dequeue() {
        if (empty()) throw std::runtime_error("Cola vacia");
        int val;
        switch (mode) {
            case Tipo::FixedFront: {
                val = buf[0];
                for (size_t i = 1; i < n; ++i) buf[i - 1] = buf[i]; // shift O(n)
                --n;
                break;
            }
            case Tipo::FixedMovable: {
                val = buf[f++];
                --n;
                if (n == 0) { f = 0; r = 0; } // normaliza punteros
                break;
            }
            case Tipo::Dynamic: {
                val = buf[f];
                f = (f + 1) % cap; // movimiento circular
                --n;
                break;
            }
        }
        return val;
    }

    // Impresión del contenido lógico + metadatos
    void print() const {
        std::cout << "[";
        if (mode == Tipo::FixedFront) {
            for (size_t i = 0; i < n; ++i)
                std::cout << buf[i] << (i + 1 < n ? ", " : "");
        } else if (mode == Tipo::FixedMovable) {
            for (size_t i = 0; i < n; ++i)
                std::cout << buf[f + i] << (i + 1 < n ? ", " : "");
        } else { // Dynamic
            for (size_t i = 0; i < n; ++i)
                std::cout << buf[(f + i) % cap] << (i + 1 < n ? ", " : "");
        }
        std::cout << "] (mode="
                  << (mode == Tipo::FixedFront ? "FixedFront"
                      : mode == Tipo::FixedMovable ? "FixedMovable" : "Dynamic")
                  << ", n=" << n
                  << ", cap=" << cap
                  << ", f=" << f
                  << ", r=" << r
                  << ")\n";
    }
};

// -------------------------
// Programa de prueba (main)
// -------------------------
int main() {
    try {
        std::cout << "=== FixedFront (tam. fijo, frente fijo) ===\n";
        Cola q1(Cola::Tipo::FixedFront, 5);
        q1.enqueue(10); q1.enqueue(20); q1.enqueue(30);
        q1.print();
        std::cout << "dequeue -> " << q1.dequeue() << "\n";
        q1.print();
        q1.enqueue(40); q1.enqueue(50); q1.enqueue(60);
        q1.print();

        std::cout << "\n=== FixedMovable (tam. fijo, frente movible no circular) ===\n";
        Cola q2(Cola::Tipo::FixedMovable, 5);
        q2.enqueue(1); q2.enqueue(2); q2.enqueue(3);
        q2.print();
        std::cout << "dequeue -> " << q2.dequeue() << "\n";
        std::cout << "dequeue -> " << q2.dequeue() << "\n";
        q2.print();
        q2.enqueue(4); q2.enqueue(5); q2.enqueue(6);
        q2.print();
        q2.enqueue(7); // fuerza compactación
        q2.print();

        std::cout << "\n=== Dynamic (tam. variable) ===\n";
        Cola q3(Cola::Tipo::Dynamic, 2);
        for (int i = 100; i <= 106; ++i) {
            q3.enqueue(i);
            q3.print();
        }
        std::cout << "front -> " << q3.front() << "\n";
        std::cout << "dequeue -> " << q3.dequeue() << "\n";
        std::cout << "dequeue -> " << q3.dequeue() << "\n";
        q3.print();
        q3.enqueue(999); q3.enqueue(1000);
        q3.print();

    } catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
    }
    return 0;
}
