#pragma once
#include <string>

class Estudiante {
private:
    int id_;
    std::string nombre_;
    std::string carrera_;
    double promedio_; // 0.0 - 100.0

public:
    // Constructores
    Estudiante();
    Estudiante(int id, const std::string& nombre, const std::string& carrera, double promedio);

    // Getters
    int id() const;
    const std::string& nombre() const;
    const std::string& carrera() const;
    double promedio() const;

    // Setters
    void set_id(int id);
    void set_nombre(const std::string& nombre);
    void set_carrera(const std::string& carrera);
    void set_promedio(double promedio);

    // Representación amigable
    std::string a_texto() const;
};

// Convierte el promedio a una clave entera en centésimas (p. ej. 87.356 -> 8736)
int convertir_promedio_a_clave(double promedio);

