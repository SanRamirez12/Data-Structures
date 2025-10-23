# 🍽️ Proyecto 1 – *La Cuchara Caliente*

**Curso:** Estructuras de Datos  
**Lenguaje:** C++17  
**Institución:** Universidad Latina de Costa Rica  

---

## 👥 Desarrolladores
- **Santiago Ramírez Elizondo**  
- **Daniela Maykall Martínez**  
- **David Abarca Chaves**

---

## 📘 Descripción general

*La Cuchara Caliente* es un programa de consola desarrollado en **C++17** que simula la gestión básica de clientes en un restaurante.  
Permite registrar clientes, llevar control de sus consumos, generar tickets de cobro y mantener una lista de atención ordenada por nombre.  

El proyecto se centra en el uso **manual de listas enlazadas simples**, aplicando los principios de **Programación Orientada a Objetos (POO)** y buenas prácticas de manejo de memoria dinámica.

---

## 🎯 Objetivos del proyecto

- Implementar una **estructura de datos dinámica** (lista enlazada simple) para manejar clientes.
- Aplicar **conceptos de POO**: encapsulamiento, modularidad y separación de responsabilidades.
- Controlar la **memoria dinámica** con `new` y `delete`, evitando fugas (`memory leaks`).
- Utilizar **funciones de utilidad** y validación robusta de entradas desde consola.
- Generar **archivos de texto (.txt)** representando los tickets de cobro, con fecha y hora automáticas.

---

## 🧩 Estructura de clases

### 🧱 `Cliente`
- Representa a un cliente con nombre, número de mesa y total acumulado.
- Métodos:
  - `acumular(double monto)` — Suma montos al total (valida que no sean negativos).

### 🔗 `ListaClientes`
- Implementa una **lista enlazada simple** ordenada alfabéticamente por nombre (case-insensitive).
- Cada nodo (`struct Nodo`) contiene un `Cliente` y un puntero al siguiente nodo.
- Métodos principales:
  - `anadirClienteOrdenado(nombre, mesa)`
  - `registrarConsumo(nombre, monto)`
  - `cobrarYEliminar(nombre)` → genera un `Ticket` y elimina el cliente.
  - `listar(visit)` → recorre la lista aplicando una función visitante.
- Destructor libera todos los nodos (`delete`).

### 🧾 `Ticket`
- Representa el comprobante o factura del cliente al ser cobrado.
- Guarda:
  - `nombre`, `mesa`, `total`, `fecha`.
- Métodos:
  - `texto()` → genera una representación legible.
  - `guardarEn(carpeta)` → crea un archivo `.txt` con el ticket, incluyendo fecha y nombre.

### 💻 `main.cpp`
- Contiene la **interfaz de usuario por consola**:
  - Menú principal con opciones (agregar, consumir, cobrar, listar, salir).
  - Lectura robusta de datos (`leerInt`, `leerDouble`, `leerLinea`).
  - Validaciones que impiden errores por entradas no numéricas.
  - Control de flujo hasta que el usuario elija la opción `0`.

---

## 🧠 Conceptos aplicados

| Concepto | Descripción |
|-----------|--------------|
| **POO** | Separación en clases: Cliente, Ticket y ListaClientes. |
| **Listas enlazadas** | Uso manual de punteros (`Nodo*`) con inserción ordenada y recorrido secuencial. |
| **Memoria dinámica** | Creación y destrucción de nodos con `new` y `delete`. |
| **Validación de entrada** | Lectura de datos robusta con `try/catch` y comprobación de tipos. |
| **Manejo de archivos** | Creación automática de directorio `tickets/` y guardado de comprobantes en formato `.txt`. |
| **Buenas prácticas** | Código modular, uso de RAII implícito, destructor seguro y comentarios técnicos. |

---

## 🧱 Estructura del proyecto
Proyecto1_CucharaCaliente/
├─ include/
│ ├─ Cliente.h
│ ├─ ListaClientes.h
│ └─ Ticket.h
├─ src/
│ ├─ Cliente.cpp
│ ├─ ListaClientes.cpp
│ ├─ Ticket.cpp
│ └─ main.cpp
├─ tickets/ ← Carpeta donde se guardan los tickets .txt

## ⚙️ Compilación y ejecución

### 🔹 Opción 1 — Visual Studio 2022
1. Abrir el proyecto `.vcxproj` o crear uno nuevo de consola.
2. En **Propiedades → C/C++ → Language**, usar **C++17 (/std:c++17)**.
3. Compilar y ejecutar (Ctrl + F5).

## 🧾 Licencia

Proyecto académico sin fines comerciales.  
© 2025 – Universidad Latina de Costa Rica
Desarrollado por: Santiago Ramírez Elizondo, Daniela Maykall Martínez y David Abarca Chaves.


