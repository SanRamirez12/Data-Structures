#include <iostream>                           // iostream para imprimir en consola (std::cout, std::endl)
#include <vector>                             // vector para manejar el buffer subyacente sin gestionar new/delete
#include <stdexcept>                          // std::runtime_error para reportar errores mediante excepciones

// La clase Cola implementa tres variantes en una sola API:
// 1) FixedFront   : tamaño fijo, frente fijo (dequeue hace shift O(n))
// 2) FixedMovable : tamaño fijo, frente movible (no circular) con compactación diferida
// 3) Dynamic      : tamaño variable, buffer circular con crecimiento (duplica capacidad)
class Cola {
public:                                       // Sección pública: visible desde fuera de la clase
    enum class Tipo {                         // enum fuertemente tipado para el modo de funcionamiento
        FixedFront   = 1,                     // Modo 1: fijo/fijo
        FixedMovable = 2,                     // Modo 2: fijo/movible (no circular; compacta cuando es necesario)
        Dynamic      = 3                      // Modo 3: dinámico (circular + crecer al llenarse)
    };

private:                                      // Sección privada: sólo la clase puede acceder
    Tipo mode;                                // Modo actual de la cola
    std::vector<int> buf;                     // Arreglo subyacente de almacenamiento
    size_t cap;                               // Capacidad lógica del buffer (fija o actual)
    size_t n;                                 // Número de elementos almacenados actualmente
    size_t f;                                 // Índice del frente (usado por FixedMovable y Dynamic)
    size_t r;                                 // Índice de inserción (rear) para FixedMovable; en Dynamic se calcula

    // --- Función auxiliar: compacta sólo en FixedMovable cuando r llegó al final y hay huecos al inicio ---
    void compact_if_needed() {                // No hace nada para otros modos
        if (mode != Tipo::FixedMovable)       // Si no es modo 2, salir
            return;                           // Sin acción

        if (r == cap && f > 0) {              // Si el puntero de inserción llegó al final y existe espacio libre delante
            for (size_t i = 0; i < n; ++i)    // Recorremos los n elementos válidos
                buf[i] = buf[f + i];          // Movemos cada elemento al inicio del buffer
            f = 0;                            // Reiniciamos frente a 0 (ya compactado)
            r = n;                            // Rear queda inmediatamente después del último elemento válido
        }
    }

    // --- Función auxiliar: crece (duplica) la capacidad en modo Dynamic, preservando el orden lógico ---
    void grow_if_needed() {                   // No hace nada para modos fijos
        if (mode != Tipo::Dynamic)            // Si no es modo 3, salir
            return;                           // Sin acción

        if (n < cap)                          // Si aún hay espacio, no crece
            return;                           // Sin acción

        size_t newCap = cap == 0 ? 1 : cap * 2; // Nueva capacidad: duplica (o pasa de 0→1)
        std::vector<int> nb(newCap);          // Creamos un nuevo buffer con la nueva capacidad

        for (size_t i = 0; i < n; ++i)        // Copiamos los n elementos en orden lógico
            nb[i] = buf[(f + i) % cap];       // Reconstruimos desde el frente considerando circularidad previa

        buf.swap(nb);                         // Intercambiamos buffers (buf ahora tiene la data relinealizada)
        cap = newCap;                         // Actualizamos capacidad
        f = 0;                                // El nuevo frente se alinea a 0 (datos ahora están [0..n))
        // Nota: en Dynamic no guardamos r; se calculará cuando se inserte (rear = (f + n) % cap)
    }

public:                                       // API pública
    explicit Cola(Tipo t, size_t capacity)    // Constructor: recibe modo y capacidad inicial
        : mode(t),                            // Inicializa el modo
          buf(capacity),                      // Reserva el vector con 'capacity' elementos (inicializados)
          cap(capacity),                      // Guarda la capacidad
          n(0),                               // Inicia cantidad de elementos en 0
          f(0),                               // Frente inicia en 0
          r(0) {}                             // Rear inicia en 0 (sólo útil para FixedMovable)

    bool empty() const { return n == 0; }     // Indica si la cola está vacía
    size_t size() const { return n; }         // Devuelve número de elementos
    size_t capacity() const { return cap; }   // Devuelve capacidad actual

    // Inserta un elemento al final de la cola
    void enqueue(int x) {                     // Método de inserción
        switch (mode) {                       // Según el modo, cambia el comportamiento
            case Tipo::FixedFront: {          // Modo 1: tamaño fijo + frente fijo
                if (n == cap)                 // Si está llena
                    throw std::runtime_error("Cola llena (FixedFront)"); // Lanzamos error

                buf[n++] = x;                 // Insertamos en la posición n y luego incrementamos n
                break;                        // Fin del caso FixedFront
            }
            case Tipo::FixedMovable: {        // Modo 2: tamaño fijo + frente movible (no circular)
                if (n == cap)                 // Si está llena lógicamente (no hay huecos efectivos)
                    throw std::runtime_error("Cola llena (FixedMovable)"); // Lanzamos error

                compact_if_needed();          // Si rear llegó al final y hay huecos, compacta

                if (r == cap)                 // Si después de intentar compactar sigue al final
                    throw std::runtime_error("No se pudo compactar (FixedMovable)"); // Error de programación

                buf[r++] = x;                 // Escribimos en la posición rear y avanzamos rear
                ++n;                          // Aumentamos el conteo lógico
                break;                        // Fin del caso FixedMovable
            }
            case Tipo::Dynamic: {             // Modo 3: tamaño variable (circular + crecimiento)
                grow_if_needed();             // Si está llena, duplica capacidad y relinealiza

                size_t rear = (f + n) % cap;  // Calcula el índice de inserción circular
                buf[rear] = x;                // Escribe el elemento en el índice calculado
                ++n;                          // Incrementa el número de elementos
                break;                        // Fin del caso Dynamic
            }
        }
    }

    // Devuelve (sin extraer) el elemento en el frente
    int front() const {                       // Método de consulta del frente
        if (empty())                          // Si no hay elementos
            throw std::runtime_error("Cola vacia"); // Reporta error

        if (mode == Tipo::FixedFront)         // En FixedFront el frente siempre es índice 0
            return buf[0];                    // Devuelve elemento en 0

        if (mode == Tipo::FixedMovable)       // En FixedMovable el frente es índice f
            return buf[f];                    // Devuelve elemento en f

        return buf[f];                        // En Dynamic también se usa f como frente
    }

    // Extrae y devuelve el elemento del frente
    int dequeue() {                           // Método de extracción
        if (empty())                          // Si está vacía
            throw std::runtime_error("Cola vacia"); // Reporta error

        int val;                              // Variable para almacenar el valor a devolver

        switch (mode) {                       // Según el modo, cambia la lógica
            case Tipo::FixedFront: {          // Modo 1: shift O(n) y frente fijo en 0
                val = buf[0];                 // Tomamos el primero
                for (size_t i = 1; i < n; ++i)// Recorremos desde el segundo hasta el último
                    buf[i - 1] = buf[i];      // Desplazamos cada elemento una posición a la izquierda
                --n;                          // Reducimos la cantidad de elementos
                // Nota: f siempre es 0 y no usamos r en este modo
                break;                        // Fin FixedFront
            }
            case Tipo::FixedMovable: {        // Modo 2: frente movible (no circular)
                val = buf[f++];               // Leemos el elemento en f y avanzamos f
                --n;                          // Reducimos la cantidad de elementos
                if (n == 0) {                 // Si quedó vacía
                    f = 0;                    // Normalizamos frente a 0
                    r = 0;                    // Normalizamos rear a 0 (para que vuelva a empezar linealmente)
                }
                break;                        // Fin FixedMovable
            }
            case Tipo::Dynamic: {             // Modo 3: circular
                val = buf[f];                 // Tomamos el elemento en f
                f = (f + 1) % cap;            // Avanzamos el frente de forma circular
                --n;                          // Reducimos la cantidad
                break;                        // Fin Dynamic
            }
        }
        return val;                           // Devolvemos el valor extraído
    }

    // Imprime el contenido lógico de la cola y algunos metadatos útiles
    void print() const {                      // Método de depuración visual
        std::cout << "[";                     // Abre la lista visual

        if (mode == Tipo::FixedFront) {       // Si es modo 1
            for (size_t i = 0; i < n; ++i)    // Recorre los n elementos desde 0
                std::cout << buf[i]           // Imprime cada valor almacenado
                          << (i + 1 < n ? ", " : ""); // Separa con coma salvo el último
        } else if (mode == Tipo::FixedMovable) { // Si es modo 2
            for (size_t i = 0; i < n; ++i)    // Recorre los n elementos desde f linealmente
                std::cout << buf[f + i]       // Imprime desde f hasta r-1
                          << (i + 1 < n ? ", " : ""); // Separador
        } else {                              // Si es modo 3 (Dynamic)
            for (size_t i = 0; i < n; ++i)    // Recorre los n elementos en orden lógico circular
                std::cout << buf[(f + i) % cap]      // Calcula índice circular
                          << (i + 1 < n ? ", " : ""); // Separador
        }

        std::cout << "]";                     // Cierra la lista
        std::cout << " (mode="               // Abre metadatos
                  << (mode == Tipo::FixedFront   ? "FixedFront" :
                      mode == Tipo::FixedMovable ? "FixedMovable" : "Dynamic") // Nombre del modo
                  << ", n=" << n             // Cantidad de elementos
                  << ", cap=" << cap         // Capacidad actual
                  << ", f=" << f             // Índice del frente
                  << ", r=" << r             // Índice de inserción (relevante para FixedMovable)
                  << ")\n";                  // Cierra metadatos y línea
    }
};                                           // Fin de la clase Cola

// -------------------------
// Programa de prueba (main)
// -------------------------
int main() {                                  // Punto de entrada del programa
    try {                                     // Bloque para capturar excepciones y mostrar errores limpios

        std::cout << "=== FixedFront (tam. fijo, frente fijo) ===\n"; // Encabezado sección 1
        Cola q1(Cola::Tipo::FixedFront, 5);   // Crea una cola modo 1 con capacidad 5
        q1.enqueue(10); q1.enqueue(20); q1.enqueue(30); // Encola tres elementos
        q1.print();                            // Muestra: [10, 20, 30]
        std::cout << "dequeue -> "            // Mensaje previo a extracción
                  << q1.dequeue() << "\n";    // Extrae y muestra el valor (hace shift)
        q1.print();                            // Muestra estado después del dequeue
        q1.enqueue(40); q1.enqueue(50); q1.enqueue(60); // Completa hasta capacidad
        q1.print();                            // Estado final de q1

        std::cout << "\n=== FixedMovable (tam. fijo, frente movible no circular) ===\n"; // Encabezado sección 2
        Cola q2(Cola::Tipo::FixedMovable, 5); // Crea una cola modo 2 con capacidad 5
        q2.enqueue(1); q2.enqueue(2); q2.enqueue(3); // Encola tres elementos
        q2.print();                            // Muestra su estado
        std::cout << "dequeue -> " << q2.dequeue() << "\n"; // Extrae uno (f avanza)
        std::cout << "dequeue -> " << q2.dequeue() << "\n"; // Extrae otro (f avanza)
        q2.print();                            // Queda con huecos al frente
        q2.enqueue(4); q2.enqueue(5); q2.enqueue(6); // r llega al final de buffer
        q2.print();                            // Aún no compacta hasta que necesite un espacio más
        q2.enqueue(7);                         // Fuerza compactación y luego inserta
        q2.print();                            // Estado luego de compactar

        std::cout << "\n=== Dynamic (tam. variable) ===\n"; // Encabezado sección 3
        Cola q3(Cola::Tipo::Dynamic, 2);       // Crea una cola modo 3 con capacidad inicial 2
        for (int i = 100; i <= 106; ++i) {     // Inserta 7 elementos para forzar crecimientos (2->4->8)
            q3.enqueue(i);                      // Encola el valor i
            q3.print();                         // Muestra el estado tras cada inserción
        }
        std::cout << "front -> "                // Mensaje para consultar el frente
                  << q3.front() << "\n";        // Muestra el elemento en el frente (sin extraer)
        std::cout << "dequeue -> "              // Texto previo a extracción
                  << q3.dequeue() << "\n";      // Extrae y muestra uno
        std::cout << "dequeue -> "              // Texto previo a extracción
                  << q3.dequeue() << "\n";      // Extrae y muestra otro
        q3.print();                              // Muestra el estado tras dos extracciones
        q3.enqueue(999); q3.enqueue(1000);      // Inserta dos valores adicionales
        q3.print();                              // Muestra el estado final

    } catch (const std::exception& ex) {        // Captura cualquier excepción lanzada en el try
        std::cerr << "ERROR: " << ex.what() << "\n"; // Imprime el mensaje de error en stderr
    }
    return 0;                                    // Retorna 0: fin correcto del programa
}
